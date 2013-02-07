Paquet description
==================

This paquet format is used to communicate between the dispatcher and the nodes.

=====  =================
Bytes  Block description
=====  =================
8      client ID (MAC ?)
1      cluster ID
1      opcode
8      size of the block
size   data
=====  =================


Opcodes
=======

These opcodes determines the nature of the instruction.  The range 0-63 is
reserved for the protocol itself and the range 64-255 is used by extensions.

====== ===========   ============================
Opcode Name          Description
====== ===========   ============================
0x00   NOP           do nothing
0x01   ASK_TASK      ask to be assigned to a task
0x02   PUSH_TASK     push a task to a node
0x03   SEND_RESULT   send the result back
====== ===========   ============================
