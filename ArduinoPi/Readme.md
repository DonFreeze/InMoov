Request message:
	Startbyte | Component | OP-Type | Typenumber | Data1 | Data2 | Endbyte

Startbyte:	'S'
Component:
	Motor:	'M'
	Eye:	'E'
	Ping:	'P'
OP-Type:
	Read:	'R'
	Write:	'W'
Typenumber:	value to select one component form selected type
Data1:		first data value for component
Data2:		second data value for component

Reply message:
Returns received message when command was executed successfully.
Returns error messages for non interpretable messages.


