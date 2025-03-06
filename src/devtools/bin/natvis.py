import typing
import lldb
import lldb.formatters.Logger

Result = typing.Union[str, bool]


def CUtlVector_T_SummaryVis( valobj: lldb.SBValue, _, options: lldb.SBTypeSummaryOptions ) -> Result:
	""" A summary visualizer for Slice<T>, which is shown as just its size """
	_ = options
	obj: lldb.SBValue = valobj.GetNonSyntheticValue()
	pointer = obj.GetChildMemberWithName( 'm_pElements' ).GetValueAsUnsigned( 0 )
	length = obj.GetChildMemberWithName( 'm_Size' ).GetValueAsUnsigned( 0 )
	return f'len={length} ptr={hex(pointer)}'


class CUtlVector_T_SynthProvider:
	obj: lldb.SBValue
	ptr: lldb.SBValue
	typ: lldb.SBType
	len: int = 0
	typSize: int = 0

	def __init__( self, valobj: lldb.SBValue, _: dict ) -> None:
		"""
		This call should initialize the Python object using valobj as the variable to provide synthetic children for
		"""
		self.obj = valobj

	def num_children( self, max_children: int ) -> int:
		"""
		The number of children this object has.
		"""
		return min( self.len + 2, max_children )

	def get_child_at_index( self, index: int ) -> typing.Union[lldb.SBValue, None]:
		"""
		This call should return a new LLDB SBValue object representing the child at the index given as argument
		"""
		if index < 0:
			return None
		if index == 0:
			return self.obj.GetChildMemberWithName( 'm_Memory' )
		if index == 1:
			return self.obj.GetChildMemberWithName( 'm_Size' )
		# fake members
		index -= 2
		if index >= self.len:
			return None
		# noinspection PyBroadException
		try:
			offset = index * self.typSize
			return self.ptr.CreateChildAtOffset( "[" + str(index) + "]", offset, self.typ )
		except:
			return None

	def update( self ) -> None:
		"""
		This call should be used to update the internal state of this Python
		object whenever the state of the variables in LLDB changes.
		Also, this method is invoked before any other method in the interface.
		"""
		self.ptr = self.obj.GetChildMemberWithName( 'm_pElements' )
		self.len = self.obj.GetChildMemberWithName( 'm_Size' ).GetValueAsUnsigned( 0 )
		self.typ = self.ptr.GetType().GetPointeeType()
		self.typSize = self.typ.GetByteSize()

	def has_children( self ) -> bool:
		"""
		This call should return whether this object might have children.
		:return: `True`, if it does, `False` if there is no way it does.
		"""
		return self.len != 0
