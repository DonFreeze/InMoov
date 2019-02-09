Request message:
	Startbyte | Componend | OP-Type | Typenumber | Data1 | Data2 | Endbyte

Startbyte:	'S'
Componend:
	Motor:	'M'
	Eye:	'E'
	Ping:	'P'
OP-Type:
	Read:	'R'
	Write:	'W'
Typenumber:	value to select one component form selected type
Data1:		first data value for componend
Data2:		second data value for componend

Reply message:
Returns recieved message when command was executed successfully.
Returns error messages for non interpretable messages.


