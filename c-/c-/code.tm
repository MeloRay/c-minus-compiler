* >>>> initial
    0:  LDA   3, -12(3)   push global scope
    1:  LDA   4, 2(3)   set fp
* <<<< initial
* -> input
    3:   IN   1, 0, 0   read value
    4:  LDA   2, 0(4)   save old fp
    5:   LD   4, -1(4)   load new fp
    6:  LDA   3, 0(2)   load new sp = fp 
    7:   LD   7, -2(3)   load old pc
* <- intput
* <- output
    8:   LD   1, -3(4)   load output value
    9:  OUT   1, 0, 0   output ac
   10:  LDA   2, 0(4)   save old fp
   11:   LD   4, -1(4)   load new fp
   12:  LDA   3, 0(2)   load new sp = fp 
   13:   LD   7, -2(3)   load old pc
* -> output
* >>>> program, 'minloc', line: 3
* >>>> compound, line: 4
   14:  LDA   3, -3(3)   push new scope
* >>>> assign, line: 6
   15:  LDA   1, -8(4)   local variable's address
   16:  LDA   3, -1(3)   add a new area
   17:   ST   1, 0(3)   push the assigned variable address
* >>>> Id, 'low', line: 6
   18:   LD   1, -4(4)   local variable
* <<<< Id, 'low', line: 6
   19:   LD   2, 0(3)   get the assigned variable address
   20:  LDA   3, 1(3)   pop tmp value
   21:   ST   1, 0(2)   assign the value
* <<<< assign, line: 6
* >>>> assign, line: 7
   22:  LDA   1, -7(4)   local variable's address
   23:  LDA   3, -1(3)   add a new area
   24:   ST   1, 0(3)   push the assigned variable address
* >>>> Array, 'a', line: 7
* >>>> Id, 'low', line: 7
   25:   LD   1, -4(4)   local variable
* <<<< Id, 'low', line: 7
   26:   LD   2, -3(4)   local variable's reference
   27:  ADD   1, 1, 2   Array index
   28:   LD   1, 0(1)   Array value
* <<<< Array, 'a', line: 7
   29:   LD   2, 0(3)   get the assigned variable address
   30:  LDA   3, 1(3)   pop tmp value
   31:   ST   1, 0(2)   assign the value
* <<<< assign, line: 7
* >>>> assign, line: 8
   32:  LDA   1, -6(4)   local variable's address
   33:  LDA   3, -1(3)   add a new area
   34:   ST   1, 0(3)   push the assigned variable address
* >>>> op, line: 8
* >>>> Id, 'low', line: 8
   35:   LD   1, -4(4)   local variable
* <<<< Id, 'low', line: 8
   36:  LDA   3, -1(3)   add new area
   37:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 8
   38:  LDC   1, 1(0)   load const
* >>>> constant, line: 8
   39:   LD   2, 0(3)   get the left operand
   40:  LDA   3, 1(3)   pop the left operand
   41:  ADD   1, 2, 1   op +
* <<<< Op, line: 8
   42:   LD   2, 0(3)   get the assigned variable address
   43:  LDA   3, 1(3)   pop tmp value
   44:   ST   1, 0(2)   assign the value
* <<<< assign, line: 8
* >>>> while, line: 9
* >>>> op, line: 9
* >>>> Id, 'i', line: 9
   45:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 9
   46:  LDA   3, -1(3)   add new area
   47:   ST   1, 0(3)   push the left operand
* >>>> Id, 'high', line: 9
   48:   LD   1, -5(4)   local variable
* <<<< Id, 'high', line: 9
   49:   LD   2, 0(3)   get the left operand
   50:  LDA   3, 1(3)   pop the left operand
   51:  SUB   1, 2, 1   op <
   52:  JLT   1, 2(7)   br if true
   53:  LDC   1, 0(1)   false case
   54:  LDA   7, 1(7)   uncoditional jmp
   55:  LDC   1, 1(1)   true case
* <<<< Op, line: 9
* while: jump to end belongs to here
* >>>> compound, line: 9
* <<<< if, line: 10
* >>>> op, line: 10
* >>>> Array, 'a', line: 10
* >>>> Id, 'i', line: 10
   57:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 10
   58:   LD   2, -3(4)   local variable's reference
   59:  ADD   1, 1, 2   Array index
   60:   LD   1, 0(1)   Array value
* <<<< Array, 'a', line: 10
   61:  LDA   3, -1(3)   add new area
   62:   ST   1, 0(3)   push the left operand
* >>>> Id, 'x', line: 10
   63:   LD   1, -7(4)   local variable
* <<<< Id, 'x', line: 10
   64:   LD   2, 0(3)   get the left operand
   65:  LDA   3, 1(3)   pop the left operand
   66:  SUB   1, 2, 1   op <
   67:  JLT   1, 2(7)   br if true
   68:  LDC   1, 0(1)   false case
   69:  LDA   7, 1(7)   uncoditional jmp
   70:  LDC   1, 1(1)   true case
* <<<< Op, line: 10
* if: jump to else belongs here
* >>>> compound, line: 10
* >>>> assign, line: 11
   72:  LDA   1, -7(4)   local variable's address
   73:  LDA   3, -1(3)   add a new area
   74:   ST   1, 0(3)   push the assigned variable address
* >>>> Array, 'a', line: 11
* >>>> Id, 'i', line: 11
   75:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 11
   76:   LD   2, -3(4)   local variable's reference
   77:  ADD   1, 1, 2   Array index
   78:   LD   1, 0(1)   Array value
* <<<< Array, 'a', line: 11
   79:   LD   2, 0(3)   get the assigned variable address
   80:  LDA   3, 1(3)   pop tmp value
   81:   ST   1, 0(2)   assign the value
* <<<< assign, line: 11
* >>>> assign, line: 12
   82:  LDA   1, -8(4)   local variable's address
   83:  LDA   3, -1(3)   add a new area
   84:   ST   1, 0(3)   push the assigned variable address
* >>>> Id, 'i', line: 12
   85:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 12
   86:   LD   2, 0(3)   get the assigned variable address
   87:  LDA   3, 1(3)   pop tmp value
   88:   ST   1, 0(2)   assign the value
* <<<< assign, line: 12
* <<<< compound, line: 10
* if: jump to end belongs here
   71:  JEQ   1, 18(7)   if: jmp to else
   89:  LDA   7, 0(7)   if: jump to end
* >>>> if, line: 10
* >>>> assign, line: 14
   90:  LDA   1, -6(4)   local variable's address
   91:  LDA   3, -1(3)   add a new area
   92:   ST   1, 0(3)   push the assigned variable address
* >>>> op, line: 14
* >>>> Id, 'i', line: 14
   93:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 14
   94:  LDA   3, -1(3)   add new area
   95:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 14
   96:  LDC   1, 1(0)   load const
* >>>> constant, line: 14
   97:   LD   2, 0(3)   get the left operand
   98:  LDA   3, 1(3)   pop the left operand
   99:  ADD   1, 2, 1   op +
* <<<< Op, line: 14
  100:   LD   2, 0(3)   get the assigned variable address
  101:  LDA   3, 1(3)   pop tmp value
  102:   ST   1, 0(2)   assign the value
* <<<< assign, line: 14
* <<<< compound, line: 9
  103:  LDA   7, -59(7)   while: jump to condition
   56:  JEQ   1, 47(7)   while: jump to end
* <<<< while, line: 9
* >>>> return, line: 17
* >>>> Id, 'k', line: 17
  104:   LD   1, -8(4)   local variable
* <<<< Id, 'k', line: 17
  105:  LDA   2, 0(4)   save old fp
  106:   LD   4, -1(4)   load new fp
  107:  LDA   3, 0(2)   load new sp = fp
  108:   LD   7, -2(3)   load old pc
* <<<< return, line: 17
  109:  LDA   3, 3(3)   pop old scope
* <<<< compound, line: 4
  110:  LDA   2, 0(4)   save old fp
  111:   LD   4, -1(4)   load new fp
  112:  LDA   3, 0(2)   load new sp = fp 
  113:   LD   7, -2(3)   load old pc
* <<<< program, 'minloc', line: 3
* >>>> program, 'sort', line: 20
* >>>> compound, line: 21
  114:  LDA   3, -2(3)   push new scope
* >>>> assign, line: 23
  115:  LDA   1, -6(4)   local variable's address
  116:  LDA   3, -1(3)   add a new area
  117:   ST   1, 0(3)   push the assigned variable address
* >>>> Id, 'low', line: 23
  118:   LD   1, -4(4)   local variable
* <<<< Id, 'low', line: 23
  119:   LD   2, 0(3)   get the assigned variable address
  120:  LDA   3, 1(3)   pop tmp value
  121:   ST   1, 0(2)   assign the value
* <<<< assign, line: 23
* >>>> while, line: 24
* >>>> op, line: 24
* >>>> Id, 'i', line: 24
  122:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 24
  123:  LDA   3, -1(3)   add new area
  124:   ST   1, 0(3)   push the left operand
* >>>> op, line: 24
* >>>> Id, 'high', line: 24
  125:   LD   1, -5(4)   local variable
* <<<< Id, 'high', line: 24
  126:  LDA   3, -1(3)   add new area
  127:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 24
  128:  LDC   1, 1(0)   load const
* >>>> constant, line: 24
  129:   LD   2, 0(3)   get the left operand
  130:  LDA   3, 1(3)   pop the left operand
  131:  SUB   1, 2, 1   op -
* <<<< Op, line: 24
  132:   LD   2, 0(3)   get the left operand
  133:  LDA   3, 1(3)   pop the left operand
  134:  SUB   1, 2, 1   op <
  135:  JLT   1, 2(7)   br if true
  136:  LDC   1, 0(1)   false case
  137:  LDA   7, 1(7)   uncoditional jmp
  138:  LDC   1, 1(1)   true case
* <<<< Op, line: 24
* while: jump to end belongs to here
* >>>> compound, line: 24
  140:  LDA   3, -1(3)   push new scope
* >>>> assign, line: 26
  141:  LDA   1, -7(4)   local variable's address
  142:  LDA   3, -1(3)   add a new area
  143:   ST   1, 0(3)   push the assigned variable address
* <<<< call, 'minloc', line: 26
  144:  LDA   3, -5(3)   load new sp
  145:   LD   1, -3(4)   pram reference
  146:   ST   1, 2(3)   load param
* >>>> Id, 'i', line: 26
  147:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 26
  148:   ST   1, 1(3)   load param
* >>>> Id, 'high', line: 26
  149:   LD   1, -5(4)   local variable
* <<<< Id, 'high', line: 26
  150:   ST   1, 0(3)   load param
  151:   ST   4, 4(3)   save old fp
  152:  LDA   4, 5(3)   load new fp
  153:  LDA   1, 2(7)   save old pc
  154:   ST   1, -2(4)   push old pc
  155:  LDA   7, -142(7)   call jmp
* <<<< call, 'minloc', line: 26
  156:   LD   2, 0(3)   get the assigned variable address
  157:  LDA   3, 1(3)   pop tmp value
  158:   ST   1, 0(2)   assign the value
* <<<< assign, line: 26
* >>>> assign, line: 27
  159:  LDA   1, -8(4)   local variable's address
  160:  LDA   3, -1(3)   add a new area
  161:   ST   1, 0(3)   push the assigned variable address
* >>>> Array, 'a', line: 27
* >>>> Id, 'k', line: 27
  162:   LD   1, -7(4)   local variable
* <<<< Id, 'k', line: 27
  163:   LD   2, -3(4)   local variable's reference
  164:  ADD   1, 1, 2   Array index
  165:   LD   1, 0(1)   Array value
* <<<< Array, 'a', line: 27
  166:   LD   2, 0(3)   get the assigned variable address
  167:  LDA   3, 1(3)   pop tmp value
  168:   ST   1, 0(2)   assign the value
* <<<< assign, line: 27
* >>>> assign, line: 28
* >>>> Id, 'k', line: 28
  169:   LD   1, -7(4)   local variable
* <<<< Id, 'k', line: 28
  170:   LD   2, -3(4)   local array's address
  171:  ADD   1, 1, 2   array index
  172:  LDA   3, -1(3)   add a new area
  173:   ST   1, 0(3)   push the assigned variable address
* >>>> Array, 'a', line: 28
* >>>> Id, 'i', line: 28
  174:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 28
  175:   LD   2, -3(4)   local variable's reference
  176:  ADD   1, 1, 2   Array index
  177:   LD   1, 0(1)   Array value
* <<<< Array, 'a', line: 28
  178:   LD   2, 0(3)   get the assigned variable address
  179:  LDA   3, 1(3)   pop tmp value
  180:   ST   1, 0(2)   assign the value
* <<<< assign, line: 28
* >>>> assign, line: 29
* >>>> Id, 'i', line: 29
  181:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 29
  182:   LD   2, -3(4)   local array's address
  183:  ADD   1, 1, 2   array index
  184:  LDA   3, -1(3)   add a new area
  185:   ST   1, 0(3)   push the assigned variable address
* >>>> Id, 't', line: 29
  186:   LD   1, -8(4)   local variable
* <<<< Id, 't', line: 29
  187:   LD   2, 0(3)   get the assigned variable address
  188:  LDA   3, 1(3)   pop tmp value
  189:   ST   1, 0(2)   assign the value
* <<<< assign, line: 29
* >>>> assign, line: 30
  190:  LDA   1, -6(4)   local variable's address
  191:  LDA   3, -1(3)   add a new area
  192:   ST   1, 0(3)   push the assigned variable address
* >>>> op, line: 30
* >>>> Id, 'i', line: 30
  193:   LD   1, -6(4)   local variable
* <<<< Id, 'i', line: 30
  194:  LDA   3, -1(3)   add new area
  195:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 30
  196:  LDC   1, 1(0)   load const
* >>>> constant, line: 30
  197:   LD   2, 0(3)   get the left operand
  198:  LDA   3, 1(3)   pop the left operand
  199:  ADD   1, 2, 1   op +
* <<<< Op, line: 30
  200:   LD   2, 0(3)   get the assigned variable address
  201:  LDA   3, 1(3)   pop tmp value
  202:   ST   1, 0(2)   assign the value
* <<<< assign, line: 30
  203:  LDA   3, 1(3)   pop old scope
* <<<< compound, line: 24
  204:  LDA   7, -83(7)   while: jump to condition
  139:  JEQ   1, 65(7)   while: jump to end
* <<<< while, line: 24
  205:  LDA   3, 2(3)   pop old scope
* <<<< compound, line: 21
  206:  LDA   2, 0(4)   save old fp
  207:   LD   4, -1(4)   load new fp
  208:  LDA   3, 0(2)   load new sp = fp 
  209:   LD   7, -2(3)   load old pc
* <<<< program, 'sort', line: 20
* >>>> program, 'main', line: 34
* >>>> compound, line: 35
  210:  LDA   3, -1(3)   push new scope
* >>>> assign, line: 37
  211:  LDA   1, -3(4)   local variable's address
  212:  LDA   3, -1(3)   add a new area
  213:   ST   1, 0(3)   push the assigned variable address
* <<<< constant, line: 37
  214:  LDC   1, 0(0)   load const
* >>>> constant, line: 37
  215:   LD   2, 0(3)   get the assigned variable address
  216:  LDA   3, 1(3)   pop tmp value
  217:   ST   1, 0(2)   assign the value
* <<<< assign, line: 37
* >>>> while, line: 38
* >>>> op, line: 38
* >>>> Id, 'i', line: 38
  218:   LD   1, -3(4)   local variable
* <<<< Id, 'i', line: 38
  219:  LDA   3, -1(3)   add new area
  220:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 38
  221:  LDC   1, 10(0)   load const
* >>>> constant, line: 38
  222:   LD   2, 0(3)   get the left operand
  223:  LDA   3, 1(3)   pop the left operand
  224:  SUB   1, 2, 1   op <
  225:  JLT   1, 2(7)   br if true
  226:  LDC   1, 0(1)   false case
  227:  LDA   7, 1(7)   uncoditional jmp
  228:  LDC   1, 1(1)   true case
* <<<< Op, line: 38
* while: jump to end belongs to here
* >>>> compound, line: 38
* >>>> assign, line: 39
* >>>> Id, 'i', line: 39
  230:   LD   1, -3(4)   local variable
* <<<< Id, 'i', line: 39
  231:  LDA   2, -10(6)   global array's address
  232:  ADD   1, 1, 2   array index
  233:  LDA   3, -1(3)   add a new area
  234:   ST   1, 0(3)   push the assigned variable address
* <<<< call, 'input', line: 39
  235:  LDA   3, -2(3)   load new sp
  236:   ST   4, 1(3)   save old fp
  237:  LDA   4, 2(3)   load new fp
  238:  LDA   1, 2(7)   save old pc
  239:   ST   1, -2(4)   push old pc
  240:  LDA   7, -238(7)   call jmp
* <<<< call, 'input', line: 39
  241:   LD   2, 0(3)   get the assigned variable address
  242:  LDA   3, 1(3)   pop tmp value
  243:   ST   1, 0(2)   assign the value
* <<<< assign, line: 39
* >>>> assign, line: 40
  244:  LDA   1, -3(4)   local variable's address
  245:  LDA   3, -1(3)   add a new area
  246:   ST   1, 0(3)   push the assigned variable address
* >>>> op, line: 40
* >>>> Id, 'i', line: 40
  247:   LD   1, -3(4)   local variable
* <<<< Id, 'i', line: 40
  248:  LDA   3, -1(3)   add new area
  249:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 40
  250:  LDC   1, 1(0)   load const
* >>>> constant, line: 40
  251:   LD   2, 0(3)   get the left operand
  252:  LDA   3, 1(3)   pop the left operand
  253:  ADD   1, 2, 1   op +
* <<<< Op, line: 40
  254:   LD   2, 0(3)   get the assigned variable address
  255:  LDA   3, 1(3)   pop tmp value
  256:   ST   1, 0(2)   assign the value
* <<<< assign, line: 40
* <<<< compound, line: 38
  257:  LDA   7, -40(7)   while: jump to condition
  229:  JEQ   1, 28(7)   while: jump to end
* <<<< while, line: 38
* <<<< call, 'sort', line: 43
  258:  LDA   3, -5(3)   load new sp
  259:  LDA   1, -10(6)   global variable param
  260:   ST   1, 2(3)   load param
* <<<< constant, line: 43
  261:  LDC   1, 0(0)   load const
* >>>> constant, line: 43
  262:   ST   1, 1(3)   load param
* <<<< constant, line: 43
  263:  LDC   1, 10(0)   load const
* >>>> constant, line: 43
  264:   ST   1, 0(3)   load param
  265:   ST   4, 4(3)   save old fp
  266:  LDA   4, 5(3)   load new fp
  267:  LDA   1, 2(7)   save old pc
  268:   ST   1, -2(4)   push old pc
  269:  LDA   7, -156(7)   call jmp
* <<<< call, 'sort', line: 43
* >>>> assign, line: 45
  270:  LDA   1, -3(4)   local variable's address
  271:  LDA   3, -1(3)   add a new area
  272:   ST   1, 0(3)   push the assigned variable address
* <<<< constant, line: 45
  273:  LDC   1, 0(0)   load const
* >>>> constant, line: 45
  274:   LD   2, 0(3)   get the assigned variable address
  275:  LDA   3, 1(3)   pop tmp value
  276:   ST   1, 0(2)   assign the value
* <<<< assign, line: 45
* >>>> while, line: 46
* >>>> op, line: 46
* >>>> Id, 'i', line: 46
  277:   LD   1, -3(4)   local variable
* <<<< Id, 'i', line: 46
  278:  LDA   3, -1(3)   add new area
  279:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 46
  280:  LDC   1, 10(0)   load const
* >>>> constant, line: 46
  281:   LD   2, 0(3)   get the left operand
  282:  LDA   3, 1(3)   pop the left operand
  283:  SUB   1, 2, 1   op <
  284:  JLT   1, 2(7)   br if true
  285:  LDC   1, 0(1)   false case
  286:  LDA   7, 1(7)   uncoditional jmp
  287:  LDC   1, 1(1)   true case
* <<<< Op, line: 46
* while: jump to end belongs to here
* >>>> compound, line: 46
* <<<< call, 'output', line: 47
  289:  LDA   3, -3(3)   load new sp
* >>>> Array, 'x', line: 47
* >>>> Id, 'i', line: 47
  290:   LD   1, -3(4)   local variable
* <<<< Id, 'i', line: 47
  291:  LDA   2, -10(6)   global variable
  292:  ADD   1, 1, 2   Array index
  293:   LD   1, 0(1)   Array value
* <<<< Array, 'x', line: 47
  294:   ST   1, 0(3)   load param
  295:   ST   4, 2(3)   save old fp
  296:  LDA   4, 3(3)   load new fp
  297:  LDA   1, 2(7)   save old pc
  298:   ST   1, -2(4)   push old pc
  299:  LDA   7, -292(7)   call jmp
* <<<< call, 'output', line: 47
* >>>> assign, line: 48
  300:  LDA   1, -3(4)   local variable's address
  301:  LDA   3, -1(3)   add a new area
  302:   ST   1, 0(3)   push the assigned variable address
* >>>> op, line: 48
* >>>> Id, 'i', line: 48
  303:   LD   1, -3(4)   local variable
* <<<< Id, 'i', line: 48
  304:  LDA   3, -1(3)   add new area
  305:   ST   1, 0(3)   push the left operand
* <<<< constant, line: 48
  306:  LDC   1, 1(0)   load const
* >>>> constant, line: 48
  307:   LD   2, 0(3)   get the left operand
  308:  LDA   3, 1(3)   pop the left operand
  309:  ADD   1, 2, 1   op +
* <<<< Op, line: 48
  310:   LD   2, 0(3)   get the assigned variable address
  311:  LDA   3, 1(3)   pop tmp value
  312:   ST   1, 0(2)   assign the value
* <<<< assign, line: 48
* <<<< compound, line: 46
  313:  LDA   7, -37(7)   while: jump to condition
  288:  JEQ   1, 25(7)   while: jump to end
* <<<< while, line: 46
  314:  LDA   3, 1(3)   pop old scope
* <<<< compound, line: 35
  315: HALT   0, 0, 0   END
* <<<< program, 'main', line: 34
    2:  LDA   7, 207(7)   load main function pos
