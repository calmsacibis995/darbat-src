### $ANTLR 2.7.5 (20050403): "CPP_parser.g" -> "CPPParser.py"$
### import antlr and other modules ..
import sys
import antlr

version = sys.version.split()[0]
if version < '2.2.1':
    False = 0
if version < '2.3':
    True = not False
### header action >>> 
# The statements in this block appear in both CPPLexer.py and CPPParser.py
from CPPDictionary import CPPDictionary
from LineObject import LineObject
import CPPSymbol
from var_types import * # "Do not use. Should be deleted in the next version"
from enum_types import *
### header action <<< 
### preamble action>>>
#        The statements in this block appear only in CPPParser.py and not in CPPLexer.py

# Used to control selected (level) tracing (see support.cpp)
# 1 Shows which external and member statements selected
# 2 Shows above plus all declarations/definitions
# 3 reserved for future use
# 4 and above available for user
statementTrace = 0

def trace1(s):
   if statementTrace >= 1:
       print s

def checknode(node):
   assert node is not None
   return node

CPPParser_MaxQualifiedItemSize = 500


# Limit lookahead for qualifiedItemIs()
MaxTemplateTokenScan = 200
### preamble action <<<

### import antlr.Token 
from antlr import Token
### >>>The Known Token Types <<<
SKIP                = antlr.SKIP
INVALID_TYPE        = antlr.INVALID_TYPE
EOF_TYPE            = antlr.EOF_TYPE
EOF                 = antlr.EOF
NULL_TREE_LOOKAHEAD = antlr.NULL_TREE_LOOKAHEAD
MIN_USER_TYPE       = antlr.MIN_USER_TYPE
LITERAL_template = 4
LESSTHAN = 5
GREATERTHAN = 6
LITERAL_typedef = 7
LITERAL_enum = 8
ID = 9
LCURLY = 10
SEMICOLON = 11
LITERAL_inline = 12
LITERAL_namespace = 13
RCURLY = 14
ASSIGNEQUAL = 15
COLON = 16
LITERAL_extern = 17
StringLiteral = 18
COMMA = 19
LITERAL__inline = 20
LITERAL___inline = 21
LITERAL_virtual = 22
LITERAL_explicit = 23
LITERAL_friend = 24
LITERAL__stdcall = 25
LITERAL___stdcall = 26
LITERAL_typename = 27
LITERAL___attribute__ = 28
LPAREN = 29
RPAREN = 30
LITERAL___mode__ = 31
LITERAL_const = 32
LITERAL_auto = 33
LITERAL_register = 34
LITERAL_static = 35
LITERAL_mutable = 36
LITERAL_const_cast = 37
LITERAL_volatile = 38
LITERAL_char = 39
LITERAL_wchar_t = 40
LITERAL_bool = 41
LITERAL_short = 42
LITERAL_int = 43
### "_int64" = 44
### "__int64" = 45
### "__w64" = 46
LITERAL_long = 47
LITERAL_signed = 48
LITERAL_unsigned = 49
LITERAL_float = 50
LITERAL_double = 51
LITERAL_void = 52
LITERAL__declspec = 53
LITERAL___declspec = 54
LITERAL_class = 55
LITERAL_struct = 56
LITERAL_union = 57
OPERATOR = 58
LITERAL_this = 59
LITERAL_true = 60
LITERAL_false = 61
DOT = 62
EQUALS = 63
LITERAL_public = 64
LITERAL_protected = 65
LITERAL_private = 66
OCTALINT = 67
STAR = 68
AMPERSAND = 69
LSQUARE = 70
RSQUARE = 71
TILDE = 72
ELLIPSIS = 73
LITERAL_throw = 74
LITERAL_case = 75
LITERAL_default = 76
LITERAL_if = 77
LITERAL_else = 78
LITERAL_switch = 79
LITERAL_while = 80
LITERAL_do = 81
LITERAL_for = 82
LITERAL_goto = 83
LITERAL_continue = 84
LITERAL_break = 85
LITERAL_return = 86
LITERAL_try = 87
LITERAL_catch = 88
LITERAL_using = 89
LITERAL__asm = 90
LITERAL___asm = 91
LITERAL___asm__ = 92
LITERAL_asm = 93
TIMESEQUAL = 94
DIVIDEEQUAL = 95
MINUSEQUAL = 96
PLUSEQUAL = 97
MODEQUAL = 98
SHIFTLEFTEQUAL = 99
SHIFTRIGHTEQUAL = 100
BITWISEANDEQUAL = 101
BITWISEXOREQUAL = 102
BITWISEOREQUAL = 103
QUESTIONMARK = 104
OR = 105
AND = 106
BITWISEOR = 107
BITWISEXOR = 108
NOTEQUAL = 109
EQUAL = 110
LESSTHANOREQUALTO = 111
GREATERTHANOREQUALTO = 112
SHIFTLEFT = 113
SHIFTRIGHT = 114
PLUS = 115
MINUS = 116
DIVIDE = 117
MOD = 118
DOTMBR = 119
POINTERTOMBR = 120
PLUSPLUS = 121
MINUSMINUS = 122
LITERAL_sizeof = 123
SCOPE = 124
POINTERTO = 125
LITERAL_dynamic_cast = 126
LITERAL_static_cast = 127
LITERAL_reinterpret_cast = 128
NOT = 129
LITERAL_new = 130
LITERAL__cdecl = 131
LITERAL___cdecl = 132
LITERAL__near = 133
LITERAL___near = 134
LITERAL__far = 135
LITERAL___far = 136
LITERAL___interrupt = 137
LITERAL_pascal = 138
LITERAL__pascal = 139
LITERAL___pascal = 140
LITERAL_delete = 141
DECIMALINT = 142
HEXADECIMALINT = 143
CharLiteral = 144
FLOATONE = 145
FLOATTWO = 146
Whitespace = 147
Comment = 148
CPPComment = 149
PREPROC_DIRECTIVE = 150
LineDirective = 151
Space = 152
Pragma = 153
Error = 154
EndOfLine = 155
Escape = 156
Digit = 157
Decimal = 158
LongSuffix = 159
UnsignedSuffix = 160
FloatSuffix = 161
Exponent = 162
Vocabulary = 163
Number = 164

class Parser(antlr.LLkParser):
    ### user action >>>
    # "protected:"
    # Semantic interface removed - nfd jul 05
    ### user action <<<
    
    def __init__(self, *args, **kwargs):
        antlr.LLkParser.__init__(self, *args, **kwargs)
        self.tokenNames = _tokenNames
        ### __init__ header action >>> 
        #antlrTrace(False);    // This is a dynamic trace facility for use with -traceParser etc.
        # It requires modification in LLkParser.cpp and LLkParser.hpp
        # otherwise it should be commented out (see MyReadMe.txt)
        # true shows antlr trace (can be set and reset during parsing)
        # false stops showing antlr trace 
        # Provided the parser is always generated with -traceParser this
        # facility allows trace output to be turned on or off by changing
        # the setting here from false to true or vice versa and then
        # recompiling and linking CPPParser only thus avoiding the need
        # to use antlr.Tool to re-generate the lexer and parser again. 
        # 
        
                                
        # Creates a dictionary to hold symbols with 4001 buckets, 200 scopes and 800,000 characters
        # These can be changed to suit the size of program(s) being parsed
        # nfd: The Python version uses Python's native dict, which has "infinite" capacity, so
        # the above params aren't passed in.
        self.symbols = CPPDictionary()
        
        # Set template parameter and external scopes
        # Set template parameter scope to 0
        self.templateParameterScope = self.symbols.getCurrentScopeIndex()
        self.symbols.saveScope()    # Advance currentScope from 0 to 1
        self.externalScope = self.symbols.getCurrentScopeIndex()    # Set external scope to 1
        
        # Declare predefined scope "std" in external scope
        a = CPPSymbol.CPPSymbol("std", CPPSymbol.otTypedef)
        self.symbols.define("std", a)
        
        # Global flags to allow for nested declarations
        self._td = False        # For typedef
        self._fd = False        # For friend
        self._ts = None                 # For TypeSpecifier
        self._ds = dsInvalid    # For DeclSpecifier
        
        # 0 = Function definition not being parsed
        # 1 = Parsing function name
        # 2 = Parsing function parameter list
        # 3 = Parsing function block
        self.functionDefinition = 0
        self.qualifierPrefix = "" # [0] = '\0';
        self.enclosingClass = "";
        self.assign_stmt_RHS_found = 0;
        self.in_parameter_list = False;
        self.K_and_R = False;    # used to distinguish old K & R parameter definitions
        self.in_return = False;
        self.is_address = False;
        self.is_pointer = False;
        
        # "protected:"
        ### __init__ header action <<< 
        
    def translation_unit(self):    
        node = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                self.enterExternalScope()
            if not self.inputState.guessing:
                accum = []
            _cnt3= 0
            while True:
                if (_tokenSet_0.member(self.LA(1))):
                    pass
                    ed=self.external_declaration()
                    if not self.inputState.guessing:
                        accum.append(ed)
                else:
                    break
                
                _cnt3 += 1
            if _cnt3 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            self.match(EOF_TYPE)
            if not self.inputState.guessing:
                node = self.autonode(accum)
            if not self.inputState.guessing:
                self.exitExternalScope()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_1)
            else:
                raise ex
        
        return node
    
    def external_declaration(self):    
        node = None
        
        self.K_and_R = False
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_namespace]:
                pass
                if not self.inputState.guessing:
                    trace1("%d external_declaration_11 Namespace declaration\n" % (self.LT(1).getLine()))
                dn=self.decl_namespace()
                if not self.inputState.guessing:
                    node = self.unfinishednode("namespace_decl")
            elif la1 and la1 in [SEMICOLON]:
                pass
                if not self.inputState.guessing:
                    trace1("%d external_declaration_13 Semicolon\n" % (self.LT(1).getLine()))
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
            else:
                synPredMatched7 = False
                if (self.LA(1)==LITERAL_template) and (self.LA(2)==LESSTHAN):
                    _m7 = self.mark()
                    synPredMatched7 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.match(LITERAL_template)
                        self.match(LESSTHAN)
                        self.match(GREATERTHAN)
                    except antlr.RecognitionException, pe:
                        synPredMatched7 = False
                    self.rewind(_m7)
                    self.inputState.guessing -= 1
                if synPredMatched7:
                    pass
                    if not self.inputState.guessing:
                        trace1("%d external_declaration_0 template explicit-specialisation\n" %(self.LT(1).getLine()))
                    self.match(LITERAL_template)
                    self.match(LESSTHAN)
                    self.match(GREATERTHAN)
                    d=self.declaration()
                    if not self.inputState.guessing:
                        node = self.node("template_specialisation", [d])
                else:
                    synPredMatched10 = False
                    if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                        _m10 = self.mark()
                        synPredMatched10 = True
                        self.inputState.guessing += 1
                        try:
                            pass
                            la1 = self.LA(1)
                            if False:
                                pass
                            elif la1 and la1 in [LITERAL_typedef]:
                                pass
                                self.match(LITERAL_typedef)
                            elif la1 and la1 in [LITERAL_class,LITERAL_struct,LITERAL_union]:
                                pass
                            else:
                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                
                            self.class_head()
                        except antlr.RecognitionException, pe:
                            synPredMatched10 = False
                        self.rewind(_m10)
                        self.inputState.guessing -= 1
                    if synPredMatched10:
                        pass
                        if not self.inputState.guessing:
                            trace1("%d external_declaration_1a Class definition\n" % (self.LT(1).getLine()))
                        d=self.declaration()
                        if not self.inputState.guessing:
                            node = d
                    else:
                        synPredMatched12 = False
                        if (self.LA(1)==LITERAL_template) and (self.LA(2)==LESSTHAN):
                            _m12 = self.mark()
                            synPredMatched12 = True
                            self.inputState.guessing += 1
                            try:
                                pass
                                self.template_head()
                                self.class_head()
                            except antlr.RecognitionException, pe:
                                synPredMatched12 = False
                            self.rewind(_m12)
                            self.inputState.guessing -= 1
                        if synPredMatched12:
                            pass
                            if not self.inputState.guessing:
                                trace1("%d external_declaration_1b Class template definition\n" % (self.LT(1).getLine()))
                            th=self.template_head()
                            d=self.declaration()
                            if not self.inputState.guessing:
                                node = self.node("template", [th, d])
                        else:
                            synPredMatched15 = False
                            if (self.LA(1)==LITERAL_enum) and (self.LA(2)==ID or self.LA(2)==LCURLY):
                                _m15 = self.mark()
                                synPredMatched15 = True
                                self.inputState.guessing += 1
                                try:
                                    pass
                                    self.match(LITERAL_enum)
                                    la1 = self.LA(1)
                                    if False:
                                        pass
                                    elif la1 and la1 in [ID]:
                                        pass
                                        self.match(ID)
                                    elif la1 and la1 in [LCURLY]:
                                        pass
                                    else:
                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                        
                                    self.match(LCURLY)
                                except antlr.RecognitionException, pe:
                                    synPredMatched15 = False
                                self.rewind(_m15)
                                self.inputState.guessing -= 1
                            if synPredMatched15:
                                pass
                                if not self.inputState.guessing:
                                    trace1("%d external_declaration_2 Enum definition\n" % (self.LT(1).getLine()))
                                es=self.enum_specifier()
                                la1 = self.LA(1)
                                if False:
                                    pass
                                elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                                    pass
                                    idl=self.init_declarator_list()
                                elif la1 and la1 in [SEMICOLON]:
                                    pass
                                else:
                                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                    
                                self.match(SEMICOLON)
                                if not self.inputState.guessing:
                                    self.end_of_stmt()
                                if not self.inputState.guessing:
                                    node = self.unfinishednode("enum")
                            else:
                                synPredMatched19 = False
                                if (_tokenSet_4.member(self.LA(1))) and (_tokenSet_5.member(self.LA(2))):
                                    _m19 = self.mark()
                                    synPredMatched19 = True
                                    self.inputState.guessing += 1
                                    try:
                                        pass
                                        la1 = self.LA(1)
                                        if False:
                                            pass
                                        elif la1 and la1 in [LITERAL_template]:
                                            pass
                                            self.template_head()
                                        elif la1 and la1 in [ID,LITERAL_inline,LITERAL__inline,LITERAL___inline,LITERAL_virtual,TILDE,SCOPE]:
                                            pass
                                        else:
                                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                            
                                        self.dtor_head(1)
                                        self.match(LCURLY)
                                    except antlr.RecognitionException, pe:
                                        synPredMatched19 = False
                                    self.rewind(_m19)
                                    self.inputState.guessing -= 1
                                if synPredMatched19:
                                    pass
                                    if not self.inputState.guessing:
                                        trace1("%d external_declaration_3 Destructor definition\n" % (self.LT(1).getLine()))
                                    la1 = self.LA(1)
                                    if False:
                                        pass
                                    elif la1 and la1 in [LITERAL_template]:
                                        pass
                                        th=self.template_head()
                                    elif la1 and la1 in [ID,LITERAL_inline,LITERAL__inline,LITERAL___inline,LITERAL_virtual,TILDE,SCOPE]:
                                        pass
                                    else:
                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                        
                                    dh=self.dtor_head(1)
                                    db=self.dtor_body()
                                    if not self.inputState.guessing:
                                        node = self.unfinishednode("destructor")
                                else:
                                    synPredMatched23 = False
                                    if (_tokenSet_6.member(self.LA(1))) and (_tokenSet_7.member(self.LA(2))):
                                        _m23 = self.mark()
                                        synPredMatched23 = True
                                        self.inputState.guessing += 1
                                        try:
                                            pass
                                            if (True) and (True):
                                                pass
                                                cds=self.ctor_decl_spec()
                                            else: ## <m4>
                                                    pass
                                                
                                            if not self.qualifiedItemIsOneOf(qiCtor):
                                                raise SemanticException("self.qualifiedItemIsOneOf(qiCtor)")
                                        except antlr.RecognitionException, pe:
                                            synPredMatched23 = False
                                        self.rewind(_m23)
                                        self.inputState.guessing -= 1
                                    if synPredMatched23:
                                        pass
                                        if not self.inputState.guessing:
                                            trace1("%d external_declaration_4 Constructor definition\n" % (self.LT(1).getLine()))
                                        cd=self.ctor_definition()
                                        if not self.inputState.guessing:
                                            node = self.unfinishednode("non-templated constructor")
                                    else:
                                        synPredMatched26 = False
                                        if (_tokenSet_8.member(self.LA(1))) and (_tokenSet_9.member(self.LA(2))):
                                            _m26 = self.mark()
                                            synPredMatched26 = True
                                            self.inputState.guessing += 1
                                            try:
                                                pass
                                                la1 = self.LA(1)
                                                if False:
                                                    pass
                                                elif la1 and la1 in [LITERAL_inline]:
                                                    pass
                                                    self.match(LITERAL_inline)
                                                elif la1 and la1 in [ID,OPERATOR,SCOPE]:
                                                    pass
                                                else:
                                                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                    
                                                self.scope_override()
                                                self.conversion_function_decl_or_def()
                                            except antlr.RecognitionException, pe:
                                                synPredMatched26 = False
                                            self.rewind(_m26)
                                            self.inputState.guessing -= 1
                                        if synPredMatched26:
                                            pass
                                            if not self.inputState.guessing:
                                                trace1("%d external_declaration_5 Operator function\n" % (self.LT(1).getLine()))
                                            la1 = self.LA(1)
                                            if False:
                                                pass
                                            elif la1 and la1 in [LITERAL_inline]:
                                                pass
                                                self.match(LITERAL_inline)
                                            elif la1 and la1 in [ID,OPERATOR,SCOPE]:
                                                pass
                                            else:
                                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                
                                            s=self.scope_override()
                                            cfdd=self.conversion_function_decl_or_def()
                                            if not self.inputState.guessing:
                                                node = self.unfinishednode("typecast")
                                        else:
                                            synPredMatched29 = False
                                            if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                                                _m29 = self.mark()
                                                synPredMatched29 = True
                                                self.inputState.guessing += 1
                                                try:
                                                    pass
                                                    self.declaration_specifiers()
                                                    self.function_declarator(0)
                                                    self.match(SEMICOLON)
                                                except antlr.RecognitionException, pe:
                                                    synPredMatched29 = False
                                                self.rewind(_m29)
                                                self.inputState.guessing -= 1
                                            if synPredMatched29:
                                                pass
                                                if not self.inputState.guessing:
                                                    trace1("%d external_declaration_6 Function declaration\n" % (self.LT(1).getLine()))
                                                d=self.declaration()
                                                if not self.inputState.guessing:
                                                    node = checknode(d)
                                            else:
                                                synPredMatched31 = False
                                                if (_tokenSet_10.member(self.LA(1))) and (_tokenSet_11.member(self.LA(2))):
                                                    _m31 = self.mark()
                                                    synPredMatched31 = True
                                                    self.inputState.guessing += 1
                                                    try:
                                                        pass
                                                        self.declaration_specifiers()
                                                        self.function_declarator(1)
                                                        self.match(LCURLY)
                                                    except antlr.RecognitionException, pe:
                                                        synPredMatched31 = False
                                                    self.rewind(_m31)
                                                    self.inputState.guessing -= 1
                                                if synPredMatched31:
                                                    pass
                                                    if not self.inputState.guessing:
                                                        trace1("%d external_declaration_7 Function definition\n" % (self.LT(1).getLine()))
                                                    fd=self.function_definition()
                                                    if not self.inputState.guessing:
                                                        node = fd
                                                else:
                                                    synPredMatched33 = False
                                                    if (_tokenSet_10.member(self.LA(1))) and (_tokenSet_11.member(self.LA(2))):
                                                        _m33 = self.mark()
                                                        synPredMatched33 = True
                                                        self.inputState.guessing += 1
                                                        try:
                                                            pass
                                                            self.declaration_specifiers()
                                                            self.function_declarator(1)
                                                            self.declaration()
                                                        except antlr.RecognitionException, pe:
                                                            synPredMatched33 = False
                                                        self.rewind(_m33)
                                                        self.inputState.guessing -= 1
                                                    if synPredMatched33:
                                                        pass
                                                        if not self.inputState.guessing:
                                                            self.K_and_R = True
                                                            trace1("%d external_declaration_8 K & R function definition\n" % (self.LT(1).getLine()))
                                                        fd=self.function_definition()
                                                        if not self.inputState.guessing:
                                                            node = fd
                                                    else:
                                                        synPredMatched36 = False
                                                        if (self.LA(1)==LITERAL_template) and (self.LA(2)==LESSTHAN):
                                                            _m36 = self.mark()
                                                            synPredMatched36 = True
                                                            self.inputState.guessing += 1
                                                            try:
                                                                pass
                                                                self.template_head()
                                                                self.declaration_specifiers()
                                                                la1 = self.LA(1)
                                                                if False:
                                                                    pass
                                                                elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                                                                    pass
                                                                    self.init_declarator_list()
                                                                elif la1 and la1 in [SEMICOLON]:
                                                                    pass
                                                                else:
                                                                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                    
                                                                self.match(SEMICOLON)
                                                                if not self.inputState.guessing:
                                                                    self.end_of_stmt()
                                                            except antlr.RecognitionException, pe:
                                                                synPredMatched36 = False
                                                            self.rewind(_m36)
                                                            self.inputState.guessing -= 1
                                                        if synPredMatched36:
                                                            pass
                                                            if not self.inputState.guessing:
                                                                self.beginTemplateDeclaration()
                                                                trace1("%d external_declaration_9 Class template declaration\n" % (self.LT(1).getLine()))
                                                            th=self.template_head()
                                                            ds=self.declaration_specifiers()
                                                            la1 = self.LA(1)
                                                            if False:
                                                                pass
                                                            elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                                                                pass
                                                                idl=self.init_declarator_list()
                                                            elif la1 and la1 in [SEMICOLON]:
                                                                pass
                                                            else:
                                                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                
                                                            self.match(SEMICOLON)
                                                            if not self.inputState.guessing:
                                                                self.end_of_stmt()
                                                            if not self.inputState.guessing:
                                                                self.endTemplateDeclaration()
                                                            if not self.inputState.guessing:
                                                                node = self.unfinishednode("templated_forward_class_decl")
                                                        elif (self.LA(1)==LITERAL_template) and (self.LA(2)==LESSTHAN):
                                                            pass
                                                            if not self.inputState.guessing:
                                                                self.beginTemplateDefinition()
                                                            th=self.template_head()
                                                            if not self.inputState.guessing:
                                                                node = self.node("templated_function")
                                                            synPredMatched40 = False
                                                            if (_tokenSet_6.member(self.LA(1))) and (_tokenSet_7.member(self.LA(2))):
                                                                _m40 = self.mark()
                                                                synPredMatched40 = True
                                                                self.inputState.guessing += 1
                                                                try:
                                                                    pass
                                                                    self.ctor_decl_spec()
                                                                    if not self.qualifiedItemIsOneOf(qiCtor):
                                                                        raise SemanticException("self.qualifiedItemIsOneOf(qiCtor)")
                                                                except antlr.RecognitionException, pe:
                                                                    synPredMatched40 = False
                                                                self.rewind(_m40)
                                                                self.inputState.guessing -= 1
                                                            if synPredMatched40:
                                                                pass
                                                                if not self.inputState.guessing:
                                                                    trace1("%d external_declaration_10a Template constructor definition\n" % (self.LT(1).getLine()))
                                                                cd=self.ctor_definition()
                                                                if not self.inputState.guessing:
                                                                    node.add_child(cd)
                                                            else:
                                                                synPredMatched42 = False
                                                                if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                                                                    _m42 = self.mark()
                                                                    synPredMatched42 = True
                                                                    self.inputState.guessing += 1
                                                                    try:
                                                                        pass
                                                                        self.declaration_specifiers()
                                                                        self.function_declarator(0)
                                                                        self.match(SEMICOLON)
                                                                    except antlr.RecognitionException, pe:
                                                                        synPredMatched42 = False
                                                                    self.rewind(_m42)
                                                                    self.inputState.guessing -= 1
                                                                if synPredMatched42:
                                                                    pass
                                                                    if not self.inputState.guessing:
                                                                        trace1("%d external_declaration_10b Function template declaration\n" % (self.LT(1).getLine()))
                                                                    d=self.declaration()
                                                                    if not self.inputState.guessing:
                                                                        node.add_child(d)
                                                                else:
                                                                    synPredMatched44 = False
                                                                    if (_tokenSet_10.member(self.LA(1))) and (_tokenSet_11.member(self.LA(2))):
                                                                        _m44 = self.mark()
                                                                        synPredMatched44 = True
                                                                        self.inputState.guessing += 1
                                                                        try:
                                                                            pass
                                                                            self.declaration_specifiers()
                                                                            self.function_declarator(1)
                                                                            self.match(LCURLY)
                                                                        except antlr.RecognitionException, pe:
                                                                            synPredMatched44 = False
                                                                        self.rewind(_m44)
                                                                        self.inputState.guessing -= 1
                                                                    if synPredMatched44:
                                                                        pass
                                                                        if not self.inputState.guessing:
                                                                            trace1("%d external_declaration_10c Function template definition\n" % (self.LT(1).getLine()))
                                                                        fd=self.function_definition()
                                                                        if not self.inputState.guessing:
                                                                            node.add_child(fd)
                                                                    else:
                                                                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                    
                                                            if not self.inputState.guessing:
                                                                self.endTemplateDefinition()
                                                        elif (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                                                            pass
                                                            if not self.inputState.guessing:
                                                                trace1("%d external_declaration_12 Declaration\n" % (self.LT(1).getLine()))
                                                            d=self.declaration()
                                                            if not self.inputState.guessing:
                                                                node = d
                                                        else:
                                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                        
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        return node
    
    def declaration(self):    
        node = None
        
        try:      ## for error handling
            synPredMatched104 = False
            if (self.LA(1)==LITERAL_extern) and (self.LA(2)==StringLiteral):
                _m104 = self.mark()
                synPredMatched104 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.match(LITERAL_extern)
                    self.match(StringLiteral)
                except antlr.RecognitionException, pe:
                    synPredMatched104 = False
                self.rewind(_m104)
                self.inputState.guessing -= 1
            if synPredMatched104:
                pass
                self.linkage_specification()
                if not self.inputState.guessing:
                    node = self.unfinishednode()
            elif (_tokenSet_13.member(self.LA(1))) and (_tokenSet_14.member(self.LA(2))):
                pass
                if not self.inputState.guessing:
                    self.beginDeclaration()
                ds=self.declaration_specifiers()
                if not self.inputState.guessing:
                    node = self.autonode([ds])
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID,COMMA,LITERAL__stdcall,LITERAL___stdcall,LITERAL___attribute__,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [COMMA]:
                        pass
                        self.match(COMMA)
                    elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LITERAL___attribute__,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL___attribute__]:
                        pass
                        a=self.attribute()
                    elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    idl=self.init_declarator_list()
                    if not self.inputState.guessing:
                        node.add_child(idl)
                elif la1 and la1 in [SEMICOLON]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    self.endDeclaration()
            elif (self.LA(1)==LITERAL_using):
                pass
                ud=self.using_declaration()
                if not self.inputState.guessing:
                    node = ud
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_15)
            else:
                raise ex
        
        return node
    
    def class_head(self):    
        node = None
        
        id = None
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                node = self.autonode(); node_leaves = []
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_struct]:
                pass
                self.match(LITERAL_struct)
                if not self.inputState.guessing:
                    node_leaves.append("struct")
            elif la1 and la1 in [LITERAL_union]:
                pass
                self.match(LITERAL_union)
                if not self.inputState.guessing:
                    node_leaves.append("union")
            elif la1 and la1 in [LITERAL_class]:
                pass
                self.match(LITERAL_class)
                if not self.inputState.guessing:
                    node_leaves.append("class")
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID]:
                pass
                id = self.LT(1)
                self.match(ID)
                if not self.inputState.guessing:
                    node_leaves.append(id.getText())
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LESSTHAN]:
                    pass
                    self.match(LESSTHAN)
                    tal=self.template_argument_list()
                    if not self.inputState.guessing:
                        node.add_child(tal)
                    self.match(GREATERTHAN)
                elif la1 and la1 in [LCURLY,COLON]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [COLON]:
                    pass
                    bc=self.base_clause()
                    if not self.inputState.guessing:
                        node.add_child(bc)
                elif la1 and la1 in [LCURLY]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            elif la1 and la1 in [LCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(LCURLY)
            if not self.inputState.guessing:
                node.set_leaf(node_leaves)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_1)
            else:
                raise ex
        
        return node
    
    def template_head(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(LITERAL_template)
            self.match(LESSTHAN)
            tpl=self.template_parameter_list()
            self.match(GREATERTHAN)
            if not self.inputState.guessing:
                node = self.autonode([tpl])
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_16)
            else:
                raise ex
        
        return node
    
    def enum_specifier(self):    
        node = None
        
        id = None
        try:      ## for error handling
            pass
            self.match(LITERAL_enum)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY]:
                pass
                self.match(LCURLY)
                self.enumerator_list()
                self.match(RCURLY)
            elif la1 and la1 in [ID]:
                pass
                id = self.LT(1)
                self.match(ID)
                if not self.inputState.guessing:
                    self.beginEnumDefinition(id.getText())
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LCURLY]:
                    pass
                    self.match(LCURLY)
                    self.enumerator_list()
                    self.match(RCURLY)
                elif la1 and la1 in [LESSTHAN,GREATERTHAN,ID,SEMICOLON,RCURLY,ASSIGNEQUAL,COLON,COMMA,LITERAL__stdcall,LITERAL___stdcall,LITERAL___attribute__,LPAREN,RPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,LSQUARE,RSQUARE,TILDE,ELLIPSIS,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL,QUESTIONMARK,OR,AND,BITWISEOR,BITWISEXOR,NOTEQUAL,EQUAL,LESSTHANOREQUALTO,GREATERTHANOREQUALTO,SHIFTLEFT,SHIFTRIGHT,PLUS,MINUS,DIVIDE,MOD,DOTMBR,POINTERTOMBR,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    self.endEnumDefinition()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.autonode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return node
    
    def init_declarator_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            id=self.init_declarator()
            if not self.inputState.guessing:
                idl = [id]
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    id=self.init_declarator()
                    if not self.inputState.guessing:
                        idl.append(id)
                else:
                    break
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL___attribute__]:
                pass
                a=self.attribute()
            elif la1 and la1 in [SEMICOLON]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.autonode(idl)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_18)
            else:
                raise ex
        
        return node
    
    def dtor_head(self,
        definition
    ):    
        node = None
        
        try:      ## for error handling
            pass
            dds=self.dtor_decl_spec()
            dd=self.dtor_declarator(definition)
            if not self.inputState.guessing:
                node = self.autonode([dd], dds)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        return node
    
    def dtor_body(self):    
        node = None
        
        try:      ## for error handling
            pass
            cs=self.compound_statement()
            if not self.inputState.guessing:
                node = checknode(cs)
            if not self.inputState.guessing:
                self.endDestructorDefinition()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        return node
    
    def ctor_decl_spec(self):    
        node = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                node = self.autonode(); speclist = []
            while True:
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_inline,LITERAL__inline,LITERAL___inline]:
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_inline]:
                        pass
                        self.match(LITERAL_inline)
                    elif la1 and la1 in [LITERAL__inline]:
                        pass
                        self.match(LITERAL__inline)
                    elif la1 and la1 in [LITERAL___inline]:
                        pass
                        self.match(LITERAL___inline)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    if not self.inputState.guessing:
                        speclist.append("inline")
                elif la1 and la1 in [LITERAL_explicit]:
                    pass
                    self.match(LITERAL_explicit)
                    if not self.inputState.guessing:
                        speclist.append("explicit")
                else:
                        break
                    
            if not self.inputState.guessing:
                node.set_leaf(speclist)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_21)
            else:
                raise ex
        
        return node
    
    def ctor_definition(self):    
        node = None
        
        try:      ## for error handling
            pass
            ch=self.ctor_head()
            cb=self.ctor_body()
            if not self.inputState.guessing:
                self.endConstructorDefinition()
            if not self.inputState.guessing:
                node = self.autonode([ch, cb])
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        return node
    
    def scope_override(self):    
        s = None
        
        id = None
        sitem = ""
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [SCOPE]:
                pass
                self.match(SCOPE)
                if not self.inputState.guessing:
                    sitem += "::"
            elif la1 and la1 in [ID,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,TILDE]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            while True:
                if ((self.LA(1)==ID) and (self.LA(2)==LESSTHAN or self.LA(2)==SCOPE) and (self.scopedItem())):
                    pass
                    id = self.LT(1)
                    self.match(ID)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LESSTHAN]:
                        pass
                        self.match(LESSTHAN)
                        tal=self.template_argument_list()
                        self.match(GREATERTHAN)
                    elif la1 and la1 in [SCOPE]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(SCOPE)
                    if not self.inputState.guessing:
                        #printf("scope_override entered\n");
                        sitem += id.getText() + "::"
                else:
                    break
                
            if not self.inputState.guessing:
                s = sitem;
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_22)
            else:
                raise ex
        
        return s
    
    def conversion_function_decl_or_def(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(OPERATOR)
            ds=self.declaration_specifiers()
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [STAR]:
                pass
                self.match(STAR)
            elif la1 and la1 in [AMPERSAND]:
                pass
                self.match(AMPERSAND)
            elif la1 and la1 in [LESSTHAN,LPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LESSTHAN]:
                pass
                self.match(LESSTHAN)
                tpl=self.template_parameter_list()
                self.match(GREATERTHAN)
            elif la1 and la1 in [LPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                pass
                pl=self.parameter_list()
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_const,LITERAL_const_cast,LITERAL_volatile]:
                pass
                tq=self.type_qualifier()
            elif la1 and la1 in [LCURLY,SEMICOLON,LITERAL_throw]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_throw]:
                pass
                es=self.exception_specification()
            elif la1 and la1 in [LCURLY,SEMICOLON]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY]:
                pass
                cs=self.compound_statement()
            elif la1 and la1 in [SEMICOLON]:
                pass
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        return node
    
    def declaration_specifiers(self):    
        node = None
        
        self._td = False
        self._fd = False
        self._ts = None
        self._ds = dsInvalid
        
        td = False
        fd = False
        ts = None
        ds = dsInvalid
        tq = None
        sc = None
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                specnames = []
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,SCOPE]:
                pass
                while True:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_extern,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable]:
                        pass
                        sc=self.storage_class_specifier()
                        if not self.inputState.guessing:
                            specnames.append(sc)
                    elif la1 and la1 in [LITERAL_const,LITERAL_const_cast,LITERAL_volatile]:
                        pass
                        tq=self.type_qualifier()
                        if not self.inputState.guessing:
                            specnames.append(tq)
                    elif la1 and la1 in [LITERAL_inline,LITERAL__inline,LITERAL___inline]:
                        pass
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LITERAL_inline]:
                            pass
                            self.match(LITERAL_inline)
                        elif la1 and la1 in [LITERAL__inline]:
                            pass
                            self.match(LITERAL__inline)
                        elif la1 and la1 in [LITERAL___inline]:
                            pass
                            self.match(LITERAL___inline)
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        if not self.inputState.guessing:
                            ds = dsINLINE
                        if not self.inputState.guessing:
                            specnames.append("inline")
                    elif la1 and la1 in [LITERAL_virtual]:
                        pass
                        self.match(LITERAL_virtual)
                        if not self.inputState.guessing:
                            ds = dsVIRTUAL
                        if not self.inputState.guessing:
                            specnames.append("virtual")
                    elif la1 and la1 in [LITERAL_explicit]:
                        pass
                        self.match(LITERAL_explicit)
                        if not self.inputState.guessing:
                            ds = dsEXPLICIT
                        if not self.inputState.guessing:
                            specnames.append("explicit")
                    elif la1 and la1 in [LITERAL_typedef]:
                        pass
                        self.match(LITERAL_typedef)
                        if not self.inputState.guessing:
                            td=True
                        if not self.inputState.guessing:
                            specnames.append("typedef")
                    elif la1 and la1 in [LITERAL_friend]:
                        pass
                        self.match(LITERAL_friend)
                        if not self.inputState.guessing:
                            fd=True
                        if not self.inputState.guessing:
                            specnames.append("friend")
                    elif la1 and la1 in [LITERAL__stdcall,LITERAL___stdcall]:
                        pass
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LITERAL__stdcall]:
                            pass
                            self.match(LITERAL__stdcall)
                        elif la1 and la1 in [LITERAL___stdcall]:
                            pass
                            self.match(LITERAL___stdcall)
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        if not self.inputState.guessing:
                            specnames.append("stdcall")
                    else:
                            break
                        
                ts=self.type_specifier(ds)
                if not self.inputState.guessing:
                    node = self.autonode([ts], specnames); node.set_result(ts.result)
            elif la1 and la1 in [LITERAL_typename]:
                pass
                self.match(LITERAL_typename)
                if not self.inputState.guessing:
                    td=True;
                dd=self.direct_declarator()
                if not self.inputState.guessing:
                    node = self.autonode([dd], ["typename"])
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                self.declarationSpecifier(td,fd,sc,tq,ts,ds)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return node
    
    def function_declarator(self,
        definition
    ):    
        node = None
        
        try:      ## for error handling
            synPredMatched230 = False
            if (_tokenSet_23.member(self.LA(1))) and (_tokenSet_24.member(self.LA(2))):
                _m230 = self.mark()
                synPredMatched230 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.ptr_operator()
                except antlr.RecognitionException, pe:
                    synPredMatched230 = False
                self.rewind(_m230)
                self.inputState.guessing -= 1
            if synPredMatched230:
                pass
                po=self.ptr_operator()
                fd=self.function_declarator(definition)
                if not self.inputState.guessing:
                    node = self.autonode([fd], po)
            elif (_tokenSet_25.member(self.LA(1))) and (_tokenSet_26.member(self.LA(2))):
                pass
                fdd=self.function_direct_declarator(definition)
                if not self.inputState.guessing:
                    node = self.autonode(None, fdd)
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_27)
            else:
                raise ex
        
        return node
    
    def function_definition(self):    
        node = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                self.beginFunctionDefinition()
            if ((_tokenSet_13.member(self.LA(1))) and (_tokenSet_28.member(self.LA(2))) and (( not (self.LA(1)==SCOPE or self.LA(1)==ID) or self.qualifiedItemIsOneOf(qiType|qiCtor) ))):
                pass
                ds=self.declaration_specifiers()
                fd=self.function_declarator(1)
                if not self.inputState.guessing:
                    decl_node = self.node("declaration_list")
                if (_tokenSet_29.member(self.LA(1))) and (_tokenSet_30.member(self.LA(2))):
                    pass
                    while True:
                        if (_tokenSet_2.member(self.LA(1))):
                            pass
                            d=self.declaration()
                            if not self.inputState.guessing:
                                decl_node.add_child(d)
                        else:
                            break
                        
                    if not self.inputState.guessing:
                        self.in_parameter_list = False
                elif (self.LA(1)==LCURLY) and (_tokenSet_31.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
                cs=self.compound_statement()
                if not self.inputState.guessing:
                    node = self.autonode([ds, fd, decl_node, cs])
            elif (_tokenSet_32.member(self.LA(1))) and (_tokenSet_33.member(self.LA(2))):
                pass
                fd=self.function_declarator(1)
                if not self.inputState.guessing:
                    decl_node = self.node("declaration_list")
                if (_tokenSet_29.member(self.LA(1))) and (_tokenSet_30.member(self.LA(2))):
                    pass
                    while True:
                        if (_tokenSet_2.member(self.LA(1))):
                            pass
                            d=self.declaration()
                        else:
                            break
                        
                    if not self.inputState.guessing:
                        decl_node.add_child(d)
                    if not self.inputState.guessing:
                        self.in_parameter_list = False
                elif (self.LA(1)==LCURLY) and (_tokenSet_31.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
                cs=self.compound_statement()
                if not self.inputState.guessing:
                    node = self.autonode([fd, decl_node, cs])
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
            if not self.inputState.guessing:
                self.endFunctionDefinition()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        return node
    
    def decl_namespace(self):    
        node = None
        
        ns = None
        ns2 = None
        try:      ## for error handling
            pass
            self.match(LITERAL_namespace)
            if (self.LA(1)==ID or self.LA(1)==LCURLY) and (_tokenSet_34.member(self.LA(2))):
                pass
                if not self.inputState.guessing:
                    node = self.node("namespace")
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID]:
                    pass
                    ns = self.LT(1)
                    self.match(ID)
                    if not self.inputState.guessing:
                        node.set_leaf(ns.getText())
                    if not self.inputState.guessing:
                        self._td = True
                        self.declaratorID(ns.getText(), qiType)
                elif la1 and la1 in [LCURLY]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(LCURLY)
                if not self.inputState.guessing:
                    self.enterNewLocalScope()
                while True:
                    if (_tokenSet_0.member(self.LA(1))):
                        pass
                        ed=self.external_declaration()
                        if not self.inputState.guessing:
                            node.add_child(ed)
                    else:
                        break
                    
                if not self.inputState.guessing:
                    self.exitLocalScope()
                self.match(RCURLY)
            elif (self.LA(1)==ID) and (self.LA(2)==ASSIGNEQUAL):
                pass
                if not self.inputState.guessing:
                    node = self.node("namespace_assignment")
                ns2 = self.LT(1)
                self.match(ID)
                if not self.inputState.guessing:
                    self._td = True
                    self.declaratorID(ns2.getText(), qiType)
                self.match(ASSIGNEQUAL)
                qid=self.qualified_id()
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node.set_leaf([ns2.getText(), qid])
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        return node
    
    def qualified_id(self):    
        q = None
        
        id = None
        try:      ## for error handling
            pass
            so=self.scope_override()
            if not self.inputState.guessing:
                qitem = so
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID]:
                pass
                id = self.LT(1)
                self.match(ID)
                if (self.LA(1)==LESSTHAN) and (_tokenSet_35.member(self.LA(2))):
                    pass
                    self.match(LESSTHAN)
                    tal=self.template_argument_list()
                    self.match(GREATERTHAN)
                elif (_tokenSet_36.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
                if not self.inputState.guessing:
                    qitem += id.getText()
            elif la1 and la1 in [OPERATOR]:
                pass
                self.match(OPERATOR)
                o=self.optor()
                if not self.inputState.guessing:
                    qitem += "operator"; qitem += o
            elif la1 and la1 in [LITERAL_this]:
                pass
                self.match(LITERAL_this)
            elif la1 and la1 in [LITERAL_true,LITERAL_false]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_true]:
                    pass
                    self.match(LITERAL_true)
                elif la1 and la1 in [LITERAL_false]:
                    pass
                    self.match(LITERAL_false)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                q = qitem
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_36)
            else:
                raise ex
        
        return q
    
    def member_declaration(self):    
        node = None
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_public,LITERAL_protected,LITERAL_private]:
                pass
                if not self.inputState.guessing:
                    trace1("%d member_declaration_14 Access specifier\n" % (self.LT(1).getLine()))
                as=self.access_specifier()
                self.match(COLON)
                if not self.inputState.guessing:
                    node = self.node(as)
            elif la1 and la1 in [SEMICOLON]:
                pass
                if not self.inputState.guessing:
                    trace1("%d member_declaration_15 Semicolon\n" % (self.LT(1).getLine()))
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node = self.unfinishednode("member-decl-524")
            else:
                synPredMatched54 = False
                if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                    _m54 = self.mark()
                    synPredMatched54 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LITERAL_typedef]:
                            pass
                            self.match(LITERAL_typedef)
                        elif la1 and la1 in [LITERAL_class,LITERAL_struct,LITERAL_union]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.class_head()
                    except antlr.RecognitionException, pe:
                        synPredMatched54 = False
                    self.rewind(_m54)
                    self.inputState.guessing -= 1
                if synPredMatched54:
                    pass
                    if not self.inputState.guessing:
                        trace1("%d member_declaration_1 Class definition\n" % (self.LT(1).getLine()))
                    d=self.declaration()
                    if not self.inputState.guessing:
                        node = d
                else:
                    synPredMatched57 = False
                    if (self.LA(1)==LITERAL_enum) and (self.LA(2)==ID or self.LA(2)==LCURLY):
                        _m57 = self.mark()
                        synPredMatched57 = True
                        self.inputState.guessing += 1
                        try:
                            pass
                            self.match(LITERAL_enum)
                            la1 = self.LA(1)
                            if False:
                                pass
                            elif la1 and la1 in [ID]:
                                pass
                                self.match(ID)
                            elif la1 and la1 in [LCURLY]:
                                pass
                            else:
                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                
                            self.match(LCURLY)
                        except antlr.RecognitionException, pe:
                            synPredMatched57 = False
                        self.rewind(_m57)
                        self.inputState.guessing -= 1
                    if synPredMatched57:
                        pass
                        if not self.inputState.guessing:
                            trace1("%d member_declaration_2 Enum definition\n" % (self.LT(1).getLine()))
                        if not self.inputState.guessing:
                            mdl = None
                        es=self.enum_specifier()
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [ID,COLON,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                            pass
                            mdl=self.member_declarator_list()
                        elif la1 and la1 in [SEMICOLON]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.match(SEMICOLON)
                        if not self.inputState.guessing:
                            self.end_of_stmt()
                        if not self.inputState.guessing:
                            node = self.autonode([es, mdl])
                    else:
                        synPredMatched60 = False
                        if (_tokenSet_6.member(self.LA(1))) and (_tokenSet_7.member(self.LA(2))):
                            _m60 = self.mark()
                            synPredMatched60 = True
                            self.inputState.guessing += 1
                            try:
                                pass
                                self.ctor_decl_spec()
                                if not self.qualifiedItemIsOneOf(qiCtor):
                                    raise SemanticException("self.qualifiedItemIsOneOf(qiCtor)")
                                self.ctor_declarator(0)
                                self.match(SEMICOLON)
                            except antlr.RecognitionException, pe:
                                synPredMatched60 = False
                            self.rewind(_m60)
                            self.inputState.guessing -= 1
                        if synPredMatched60:
                            pass
                            if not self.inputState.guessing:
                                trace1("%d member_declaration_3 Constructor declarator\n" % (self.LT(1).getLine()))
                            cds=self.ctor_decl_spec()
                            cd=self.ctor_declarator(0)
                            self.match(SEMICOLON)
                            if not self.inputState.guessing:
                                self.end_of_stmt()
                            if not self.inputState.guessing:
                                node = self.autonode([cds, cd])
                        else:
                            synPredMatched63 = False
                            if (_tokenSet_6.member(self.LA(1))) and (_tokenSet_7.member(self.LA(2))):
                                _m63 = self.mark()
                                synPredMatched63 = True
                                self.inputState.guessing += 1
                                try:
                                    pass
                                    self.ctor_decl_spec()
                                    if not self.qualifiedItemIsOneOf(qiCtor):
                                        raise SemanticException("self.qualifiedItemIsOneOf(qiCtor)")
                                    self.ctor_declarator(1)
                                    la1 = self.LA(1)
                                    if False:
                                        pass
                                    elif la1 and la1 in [COLON]:
                                        pass
                                        self.match(COLON)
                                    elif la1 and la1 in [LCURLY]:
                                        pass
                                        self.match(LCURLY)
                                    else:
                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                        
                                except antlr.RecognitionException, pe:
                                    synPredMatched63 = False
                                self.rewind(_m63)
                                self.inputState.guessing -= 1
                            if synPredMatched63:
                                pass
                                if not self.inputState.guessing:
                                    trace1("%d member_declaration_4 Constructor definition\n" % (self.LT(1).getLine()))
                                cd=self.ctor_definition()
                                if not self.inputState.guessing:
                                    node = self.autonode([cd])
                            else:
                                synPredMatched65 = False
                                if (_tokenSet_38.member(self.LA(1))) and (_tokenSet_5.member(self.LA(2))):
                                    _m65 = self.mark()
                                    synPredMatched65 = True
                                    self.inputState.guessing += 1
                                    try:
                                        pass
                                        self.dtor_head(0)
                                        self.match(SEMICOLON)
                                    except antlr.RecognitionException, pe:
                                        synPredMatched65 = False
                                    self.rewind(_m65)
                                    self.inputState.guessing -= 1
                                if synPredMatched65:
                                    pass
                                    if not self.inputState.guessing:
                                        trace1("%d member_declaration_5a Destructor declaration\n" % (self.LT(1).getLine()))
                                    dh=self.dtor_head(0)
                                    self.match(SEMICOLON)
                                    if not self.inputState.guessing:
                                        self.end_of_stmt()
                                    if not self.inputState.guessing:
                                        node = self.autonode([dh])
                                else:
                                    synPredMatched67 = False
                                    if (_tokenSet_38.member(self.LA(1))) and (_tokenSet_5.member(self.LA(2))):
                                        _m67 = self.mark()
                                        synPredMatched67 = True
                                        self.inputState.guessing += 1
                                        try:
                                            pass
                                            self.dtor_head(1)
                                            self.match(LCURLY)
                                        except antlr.RecognitionException, pe:
                                            synPredMatched67 = False
                                        self.rewind(_m67)
                                        self.inputState.guessing -= 1
                                    if synPredMatched67:
                                        pass
                                        if not self.inputState.guessing:
                                            trace1("%d member_declaration_5b Destructor definition\n" % (self.LT(1).getLine()))
                                        dh=self.dtor_head(1)
                                        db=self.dtor_body()
                                        if not self.inputState.guessing:
                                            node = self.autonode([dh, db])
                                    else:
                                        synPredMatched69 = False
                                        if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                                            _m69 = self.mark()
                                            synPredMatched69 = True
                                            self.inputState.guessing += 1
                                            try:
                                                pass
                                                self.declaration_specifiers()
                                                self.function_declarator(0)
                                                self.match(SEMICOLON)
                                            except antlr.RecognitionException, pe:
                                                synPredMatched69 = False
                                            self.rewind(_m69)
                                            self.inputState.guessing -= 1
                                        if synPredMatched69:
                                            pass
                                            if not self.inputState.guessing:
                                                trace1("%d member_declaration_6 Function declaration\n" % (self.LT(1).getLine()))
                                            d=self.declaration()
                                            if not self.inputState.guessing:
                                                node = d
                                        else:
                                            synPredMatched71 = False
                                            if (_tokenSet_10.member(self.LA(1))) and (_tokenSet_11.member(self.LA(2))):
                                                _m71 = self.mark()
                                                synPredMatched71 = True
                                                self.inputState.guessing += 1
                                                try:
                                                    pass
                                                    self.declaration_specifiers()
                                                    self.function_declarator(1)
                                                    self.match(LCURLY)
                                                except antlr.RecognitionException, pe:
                                                    synPredMatched71 = False
                                                self.rewind(_m71)
                                                self.inputState.guessing -= 1
                                            if synPredMatched71:
                                                pass
                                                if not self.inputState.guessing:
                                                    self.beginFieldDeclaration()
                                                    trace1("%d member_declaration_7 Function definition\n" % (self.LT(1).getLine()))
                                                fd=self.function_definition()
                                                if not self.inputState.guessing:
                                                    node = fd
                                            else:
                                                synPredMatched74 = False
                                                if (self.LA(1)==LITERAL_inline or self.LA(1)==OPERATOR) and (_tokenSet_39.member(self.LA(2))):
                                                    _m74 = self.mark()
                                                    synPredMatched74 = True
                                                    self.inputState.guessing += 1
                                                    try:
                                                        pass
                                                        la1 = self.LA(1)
                                                        if False:
                                                            pass
                                                        elif la1 and la1 in [LITERAL_inline]:
                                                            pass
                                                            self.match(LITERAL_inline)
                                                        elif la1 and la1 in [OPERATOR]:
                                                            pass
                                                        else:
                                                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                            
                                                        self.conversion_function_decl_or_def()
                                                    except antlr.RecognitionException, pe:
                                                        synPredMatched74 = False
                                                    self.rewind(_m74)
                                                    self.inputState.guessing -= 1
                                                if synPredMatched74:
                                                    pass
                                                    if not self.inputState.guessing:
                                                        trace1("%d member_declaration_8 Operator function\n" % (self.LT(1).getLine()))
                                                    la1 = self.LA(1)
                                                    if False:
                                                        pass
                                                    elif la1 and la1 in [LITERAL_inline]:
                                                        pass
                                                        self.match(LITERAL_inline)
                                                    elif la1 and la1 in [OPERATOR]:
                                                        pass
                                                    else:
                                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                        
                                                    cfdd=self.conversion_function_decl_or_def()
                                                    if not self.inputState.guessing:
                                                        node = self.unfinishednode("udtc-439")
                                                else:
                                                    synPredMatched77 = False
                                                    if (_tokenSet_40.member(self.LA(1))) and (_tokenSet_41.member(self.LA(2))):
                                                        _m77 = self.mark()
                                                        synPredMatched77 = True
                                                        self.inputState.guessing += 1
                                                        try:
                                                            pass
                                                            self.qualified_id()
                                                            self.match(SEMICOLON)
                                                        except antlr.RecognitionException, pe:
                                                            synPredMatched77 = False
                                                        self.rewind(_m77)
                                                        self.inputState.guessing -= 1
                                                    if synPredMatched77:
                                                        pass
                                                        if not self.inputState.guessing:
                                                            trace1("%d member_declaration_9 Qualified ID\n" % (self.LT(1).getLine()))
                                                        q=self.qualified_id()
                                                        self.match(SEMICOLON)
                                                        if not self.inputState.guessing:
                                                            self.end_of_stmt()
                                                        if not self.inputState.guessing:
                                                            node = self.unfinishednode("declhack-446")
                                                    else:
                                                        synPredMatched79 = False
                                                        if (_tokenSet_13.member(self.LA(1))) and (_tokenSet_42.member(self.LA(2))):
                                                            _m79 = self.mark()
                                                            synPredMatched79 = True
                                                            self.inputState.guessing += 1
                                                            try:
                                                                pass
                                                                self.declaration_specifiers()
                                                            except antlr.RecognitionException, pe:
                                                                synPredMatched79 = False
                                                            self.rewind(_m79)
                                                            self.inputState.guessing -= 1
                                                        if synPredMatched79:
                                                            pass
                                                            if not self.inputState.guessing:
                                                                self.beginFieldDeclaration()
                                                                trace1("%d member_declaration_10 Declaration(s)\n" % (self.LT(1).getLine()))
                                                            if not self.inputState.guessing:
                                                                mdl = []
                                                            ds=self.declaration_specifiers()
                                                            la1 = self.LA(1)
                                                            if False:
                                                                pass
                                                            elif la1 and la1 in [ID,COLON,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                                                                pass
                                                                md=self.member_declarator_list()
                                                                if not self.inputState.guessing:
                                                                    mdl = [md]
                                                            elif la1 and la1 in [SEMICOLON]:
                                                                pass
                                                            else:
                                                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                
                                                            self.match(SEMICOLON)
                                                            if not self.inputState.guessing:
                                                                self.end_of_stmt()
                                                            if not self.inputState.guessing:
                                                                node = self.autonode([ds] + mdl)
                                                        else:
                                                            synPredMatched82 = False
                                                            if (_tokenSet_32.member(self.LA(1))) and (_tokenSet_33.member(self.LA(2))):
                                                                _m82 = self.mark()
                                                                synPredMatched82 = True
                                                                self.inputState.guessing += 1
                                                                try:
                                                                    pass
                                                                    self.function_declarator(0)
                                                                    self.match(SEMICOLON)
                                                                except antlr.RecognitionException, pe:
                                                                    synPredMatched82 = False
                                                                self.rewind(_m82)
                                                                self.inputState.guessing -= 1
                                                            if synPredMatched82:
                                                                pass
                                                                if not self.inputState.guessing:
                                                                    self.beginFieldDeclaration()
                                                                    trace_err("%d warning Function declaration found without typename\n" % (self.LT(1).getLine()))
                                                                    trace1("%d member_declaration_11a Function declaration\n" % (self.LT(1).getLine()))
                                                                fd=self.function_declarator(0)
                                                                self.match(SEMICOLON)
                                                                if not self.inputState.guessing:
                                                                    self.end_of_stmt()
                                                                if not self.inputState.guessing:
                                                                    node = checknode(fd)
                                                            elif (_tokenSet_32.member(self.LA(1))) and (_tokenSet_33.member(self.LA(2))):
                                                                pass
                                                                if not self.inputState.guessing:
                                                                    trace_err("%d warning Function definition found without typename\n" % (self.LT(1).getLine()))
                                                                    trace1("%d member_declaration_11b Function definition\n" % (self.LT(1).getLine()))
                                                                fd=self.function_declarator(1)
                                                                cs=self.compound_statement()
                                                                if not self.inputState.guessing:
                                                                    self.endFunctionDefinition()
                                                                if not self.inputState.guessing:
                                                                    node = self.autonode([fd, cs])
                                                            else:
                                                                synPredMatched85 = False
                                                                if (self.LA(1)==LITERAL_template) and (self.LA(2)==LESSTHAN):
                                                                    _m85 = self.mark()
                                                                    synPredMatched85 = True
                                                                    self.inputState.guessing += 1
                                                                    try:
                                                                        pass
                                                                        self.template_head()
                                                                        ds=self.declaration_specifiers()
                                                                        la1 = self.LA(1)
                                                                        if False:
                                                                            pass
                                                                        elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                                                                            pass
                                                                            self.init_declarator_list()
                                                                        elif la1 and la1 in [SEMICOLON]:
                                                                            pass
                                                                        else:
                                                                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                            
                                                                        self.match(SEMICOLON)
                                                                    except antlr.RecognitionException, pe:
                                                                        synPredMatched85 = False
                                                                    self.rewind(_m85)
                                                                    self.inputState.guessing -= 1
                                                                if synPredMatched85:
                                                                    pass
                                                                    if not self.inputState.guessing:
                                                                        self.beginTemplateDeclaration()
                                                                        trace1("%d member_declaration_12 Class template declaration\n" % (self.LT(1).getLine()))
                                                                    th=self.template_head()
                                                                    ds=self.declaration_specifiers()
                                                                    if not self.inputState.guessing:
                                                                        node = self.autonode([th, ds])
                                                                    la1 = self.LA(1)
                                                                    if False:
                                                                        pass
                                                                    elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,LPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                                                                        pass
                                                                        idl=self.init_declarator_list()
                                                                        if not self.inputState.guessing:
                                                                            node.add_child(idl)
                                                                    elif la1 and la1 in [SEMICOLON]:
                                                                        pass
                                                                    else:
                                                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                        
                                                                    self.match(SEMICOLON)
                                                                    if not self.inputState.guessing:
                                                                        self.end_of_stmt()
                                                                    if not self.inputState.guessing:
                                                                        self.endTemplateDeclaration()
                                                                elif (self.LA(1)==LITERAL_template) and (self.LA(2)==LESSTHAN):
                                                                    pass
                                                                    if not self.inputState.guessing:
                                                                        self.beginTemplateDefinition()
                                                                    th=self.template_head()
                                                                    if not self.inputState.guessing:
                                                                        node = self.node("templated_function", [th])
                                                                    synPredMatched89 = False
                                                                    if (_tokenSet_6.member(self.LA(1))) and (_tokenSet_7.member(self.LA(2))):
                                                                        _m89 = self.mark()
                                                                        synPredMatched89 = True
                                                                        self.inputState.guessing += 1
                                                                        try:
                                                                            pass
                                                                            self.ctor_decl_spec()
                                                                            if not self.qualifiedItemIsOneOf(qiCtor):
                                                                                raise SemanticException("self.qualifiedItemIsOneOf(qiCtor)")
                                                                        except antlr.RecognitionException, pe:
                                                                            synPredMatched89 = False
                                                                        self.rewind(_m89)
                                                                        self.inputState.guessing -= 1
                                                                    if synPredMatched89:
                                                                        pass
                                                                        if not self.inputState.guessing:
                                                                            trace1("%d member_declaration_13a Template constructor definition\n" % (self.LT(1).getLine()))
                                                                        cd=self.ctor_definition()
                                                                        if not self.inputState.guessing:
                                                                            node.add_child(cd)
                                                                    else:
                                                                        synPredMatched91 = False
                                                                        if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                                                                            _m91 = self.mark()
                                                                            synPredMatched91 = True
                                                                            self.inputState.guessing += 1
                                                                            try:
                                                                                pass
                                                                                self.declaration_specifiers()
                                                                                self.function_declarator(0)
                                                                                self.match(SEMICOLON)
                                                                            except antlr.RecognitionException, pe:
                                                                                synPredMatched91 = False
                                                                            self.rewind(_m91)
                                                                            self.inputState.guessing -= 1
                                                                        if synPredMatched91:
                                                                            pass
                                                                            if not self.inputState.guessing:
                                                                                trace1("%d member_declaration_13b Function template declaration\n" % (self.LT(1).getLine()))
                                                                            d=self.declaration()
                                                                            if not self.inputState.guessing:
                                                                                node.add_child(d)
                                                                        else:
                                                                            synPredMatched93 = False
                                                                            if (_tokenSet_10.member(self.LA(1))) and (_tokenSet_11.member(self.LA(2))):
                                                                                _m93 = self.mark()
                                                                                synPredMatched93 = True
                                                                                self.inputState.guessing += 1
                                                                                try:
                                                                                    pass
                                                                                    self.declaration_specifiers()
                                                                                    self.function_declarator(1)
                                                                                    self.match(LCURLY)
                                                                                except antlr.RecognitionException, pe:
                                                                                    synPredMatched93 = False
                                                                                self.rewind(_m93)
                                                                                self.inputState.guessing -= 1
                                                                            if synPredMatched93:
                                                                                pass
                                                                                if not self.inputState.guessing:
                                                                                    trace1("%d member_declaration_13c Function template definition\n" % (self.LT(1).getLine()))
                                                                                fd=self.function_definition()
                                                                                if not self.inputState.guessing:
                                                                                    node.add_child(fd)
                                                                            elif (self.LA(1)==OPERATOR) and (_tokenSet_13.member(self.LA(2))):
                                                                                pass
                                                                                if not self.inputState.guessing:
                                                                                    trace1("%d member_declaration_13d Templated operator function\n" % (self.LT(1).getLine()))
                                                                                cfdd=self.conversion_function_decl_or_def()
                                                                                if not self.inputState.guessing:
                                                                                    node.add_child(cfdd)
                                                                            else:
                                                                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                            
                                                                    if not self.inputState.guessing:
                                                                        self.endTemplateDefinition()
                                                                else:
                                                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                                                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_43)
            else:
                raise ex
        
        return node
    
    def member_declarator_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            md=self.member_declarator()
            if not self.inputState.guessing:
                node = self.autonode([md])
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    md=self.member_declarator()
                    if not self.inputState.guessing:
                        node.add_child(md)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_18)
            else:
                raise ex
        
        return node
    
    def ctor_declarator(self,
        definition
    ):    
        node = None
        
        try:      ## for error handling
            pass
            q=self.qualified_ctor_id()
            if not self.inputState.guessing:
                self.declaratorParameterList(definition)
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                pass
                pl=self.parameter_list()
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
            if not self.inputState.guessing:
                self.declaratorEndParameterList(definition)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_throw]:
                pass
                es=self.exception_specification()
            elif la1 and la1 in [LCURLY,SEMICOLON,COLON]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_44)
            else:
                raise ex
        
        return node
    
    def compound_statement(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(LCURLY)
            if not self.inputState.guessing:
                self.end_of_stmt()
                self.enterNewLocalScope()
            if not self.inputState.guessing:
                node = self.autonode()
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LCURLY,SEMICOLON,LITERAL_inline,LITERAL_extern,StringLiteral,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,LITERAL_throw,LITERAL_case,LITERAL_default,LITERAL_if,LITERAL_switch,LITERAL_while,LITERAL_do,LITERAL_for,LITERAL_goto,LITERAL_continue,LITERAL_break,LITERAL_return,LITERAL_try,LITERAL_using,LITERAL__asm,LITERAL___asm,LITERAL___asm__,LITERAL_asm,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                pass
                sl=self.statement_list()
                if not self.inputState.guessing:
                    node.add_child(sl)
            elif la1 and la1 in [RCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RCURLY)
            if not self.inputState.guessing:
                self.exitLocalScope()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        return node
    
    def access_specifier(self):    
        as = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_public]:
                pass
                self.match(LITERAL_public)
                if not self.inputState.guessing:
                    as = "public"
            elif la1 and la1 in [LITERAL_protected]:
                pass
                self.match(LITERAL_protected)
                if not self.inputState.guessing:
                    as = "protected"
            elif la1 and la1 in [LITERAL_private]:
                pass
                self.match(LITERAL_private)
                if not self.inputState.guessing:
                    as = "private"
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_46)
            else:
                raise ex
        
        return as
    
    def linkage_specification(self):    
        
        try:      ## for error handling
            pass
            self.match(LITERAL_extern)
            self.match(StringLiteral)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY]:
                pass
                self.match(LCURLY)
                while True:
                    if (_tokenSet_0.member(self.LA(1))):
                        pass
                        ed=self.external_declaration()
                    else:
                        break
                    
                self.match(RCURLY)
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,LITERAL_using,SCOPE]:
                pass
                d=self.declaration()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_15)
            else:
                raise ex
        
    
    def attribute(self):    
        a = None
        
        try:      ## for error handling
            pass
            self.match(LITERAL___attribute__)
            self.match(LPAREN)
            self.match(LPAREN)
            self.attribute_decl_list()
            self.match(RPAREN)
            self.match(RPAREN)
            if not self.inputState.guessing:
                a = None
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_47)
            else:
                raise ex
        
        return a
    
    def using_declaration(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(LITERAL_using)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_namespace]:
                pass
                self.match(LITERAL_namespace)
                qid=self.qualified_id()
            elif la1 and la1 in [ID,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,SCOPE]:
                pass
                qid=self.qualified_id()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(SEMICOLON)
            if not self.inputState.guessing:
                end_of_stmt();
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_15)
            else:
                raise ex
        
        return node
    
    def storage_class_specifier(self):    
        sc = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_auto]:
                pass
                self.match(LITERAL_auto)
                if not self.inputState.guessing:
                    sc = "auto";
            elif la1 and la1 in [LITERAL_register]:
                pass
                self.match(LITERAL_register)
                if not self.inputState.guessing:
                    sc = "register";
            elif la1 and la1 in [LITERAL_static]:
                pass
                self.match(LITERAL_static)
                if not self.inputState.guessing:
                    sc = "static";
            elif la1 and la1 in [LITERAL_extern]:
                pass
                self.match(LITERAL_extern)
                if not self.inputState.guessing:
                    sc = "extern";
            elif la1 and la1 in [LITERAL_mutable]:
                pass
                self.match(LITERAL_mutable)
                if not self.inputState.guessing:
                    sc = "mutable";
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_48)
            else:
                raise ex
        
        return sc
    
    def type_qualifier(self):    
        tq = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_const,LITERAL_const_cast]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_const]:
                    pass
                    self.match(LITERAL_const)
                elif la1 and la1 in [LITERAL_const_cast]:
                    pass
                    self.match(LITERAL_const_cast)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    tq = "const";
            elif la1 and la1 in [LITERAL_volatile]:
                pass
                self.match(LITERAL_volatile)
                if not self.inputState.guessing:
                    tq = "volatile";
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_49)
            else:
                raise ex
        
        return tq
    
    def type_specifier(self,
        ds
    ):    
        ts = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,SCOPE]:
                pass
                ts=self.simple_type_specifier()
            elif la1 and la1 in [LITERAL_class,LITERAL_struct,LITERAL_union]:
                pass
                ts=self.class_specifier(ds)
            elif la1 and la1 in [LITERAL_enum]:
                pass
                ts=self.enum_specifier()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return ts
    
    def direct_declarator(self):    
        node = None
        
        dtor = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [TILDE]:
                pass
                self.match(TILDE)
                dtor = self.LT(1)
                self.match(ID)
                if not self.inputState.guessing:
                    declaratorID(dtor.getText(),qiDtor)
                if not self.inputState.guessing:
                    print "%d warning direct_declarator5 entered unexpectedly with %s" % (self.LT(1).getLine(),dtor.getText())
                self.match(LPAREN)
                if not self.inputState.guessing:
                    self.declaratorParameterList(0)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                    pass
                    pl=self.parameter_list()
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(RPAREN)
                if not self.inputState.guessing:
                    self.declaratorEndParameterList(0)
                if not self.inputState.guessing:
                    node = self.unfinishednode()
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                d=self.declarator()
                self.match(RPAREN)
                ds=self.declarator_suffixes()
                if not self.inputState.guessing:
                    node = self.autonode([d, ds])
            else:
                synPredMatched206 = False
                if (_tokenSet_40.member(self.LA(1))) and (_tokenSet_26.member(self.LA(2))):
                    _m206 = self.mark()
                    synPredMatched206 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.qualified_id()
                        self.match(LPAREN)
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [RPAREN]:
                            pass
                            self.match(RPAREN)
                        elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,SCOPE]:
                            pass
                            self.declaration_specifiers()
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                    except antlr.RecognitionException, pe:
                        synPredMatched206 = False
                    self.rewind(_m206)
                    self.inputState.guessing -= 1
                if synPredMatched206:
                    pass
                    id=self.qualified_id()
                    if not self.inputState.guessing:
                        node = self.autonode(None, id)
                    if not self.inputState.guessing:
                        self.declaratorID(id, qiFun)
                    self.match(LPAREN)
                    if not self.inputState.guessing:
                        self.declaratorParameterList(0)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                        pass
                        pl=self.parameter_list()
                        if not self.inputState.guessing:
                            node.add_child(pl)
                    elif la1 and la1 in [RPAREN]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(RPAREN)
                    if not self.inputState.guessing:
                        self.declaratorEndParameterList(0)
                    if not self.inputState.guessing:
                        tql = []
                    while True:
                        if (_tokenSet_50.member(self.LA(1))):
                            pass
                            tq=self.type_qualifier()
                            if not self.inputState.guessing:
                                tql.append(tq);node.add_child(tq)
                        else:
                            break
                        
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_throw]:
                        pass
                        es=self.exception_specification()
                        if not self.inputState.guessing:
                            node.add_child(es)
                    elif la1 and la1 in [LESSTHAN,GREATERTHAN,ID,SEMICOLON,RCURLY,ASSIGNEQUAL,COLON,COMMA,LITERAL__stdcall,LITERAL___stdcall,LITERAL___attribute__,LPAREN,RPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,LSQUARE,RSQUARE,TILDE,ELLIPSIS,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL,QUESTIONMARK,OR,AND,BITWISEOR,BITWISEXOR,NOTEQUAL,EQUAL,LESSTHANOREQUALTO,GREATERTHANOREQUALTO,SHIFTLEFT,SHIFTRIGHT,PLUS,MINUS,DIVIDE,MOD,DOTMBR,POINTERTOMBR,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                else:
                    synPredMatched212 = False
                    if (_tokenSet_40.member(self.LA(1))) and (_tokenSet_26.member(self.LA(2))):
                        _m212 = self.mark()
                        synPredMatched212 = True
                        self.inputState.guessing += 1
                        try:
                            pass
                            self.qualified_id()
                            self.match(LPAREN)
                            self.qualified_id()
                        except antlr.RecognitionException, pe:
                            synPredMatched212 = False
                        self.rewind(_m212)
                        self.inputState.guessing -= 1
                    if synPredMatched212:
                        pass
                        id=self.qualified_id()
                        if not self.inputState.guessing:
                            self.declaratorID(id,qiVar)
                        self.match(LPAREN)
                        el=self.expression_list()
                        self.match(RPAREN)
                        if not self.inputState.guessing:
                            node = self.autonode([el], id)
                    else:
                        synPredMatched214 = False
                        if (_tokenSet_40.member(self.LA(1))) and (_tokenSet_26.member(self.LA(2))):
                            _m214 = self.mark()
                            synPredMatched214 = True
                            self.inputState.guessing += 1
                            try:
                                pass
                                self.qualified_id()
                                self.match(LSQUARE)
                            except antlr.RecognitionException, pe:
                                synPredMatched214 = False
                            self.rewind(_m214)
                            self.inputState.guessing -= 1
                        if synPredMatched214:
                            pass
                            id=self.qualified_id()
                            if not self.inputState.guessing:
                                if self._td:
                                   self.declaratorID(id, qiType)
                                else:
                                   self.declaratorID(id, qiVar)
                                self.is_address = False
                                self.is_pointer = False;
                            _cnt217= 0
                            while True:
                                if (self.LA(1)==LSQUARE) and (_tokenSet_51.member(self.LA(2))):
                                    pass
                                    self.match(LSQUARE)
                                    la1 = self.LA(1)
                                    if False:
                                        pass
                                    elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                                        pass
                                        ce=self.constant_expression()
                                    elif la1 and la1 in [RSQUARE]:
                                        pass
                                    else:
                                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                        
                                    self.match(RSQUARE)
                                else:
                                    break
                                
                                _cnt217 += 1
                            if _cnt217 < 1:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            if not self.inputState.guessing:
                                self.declaratorArray()
                            if not self.inputState.guessing:
                                node = self.autonode([ce], id)
                        elif (_tokenSet_40.member(self.LA(1))) and (_tokenSet_52.member(self.LA(2))):
                            pass
                            id=self.qualified_id()
                            if not self.inputState.guessing:
                                if self._td:
                                   self.declaratorID(id,qiType)
                                else:
                                   self.declaratorID(id,qiVar)
                                self.is_address = False
                                self.is_pointer = False;
                            if not self.inputState.guessing:
                                node = self.autonode(None, id)
                        else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return node
    
    def attribute_decl_list(self):    
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL___mode__]:
                pass
                self.match(LITERAL___mode__)
                self.match(LPAREN)
                self.match(ID)
                self.match(RPAREN)
            elif la1 and la1 in [LITERAL_const]:
                pass
                self.match(LITERAL_const)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_53)
            else:
                raise ex
        
    
    def simple_type_specifier(self):    
        node = None
        
        ts = []
        try:      ## for error handling
            pass
            if ((self.LA(1)==ID or self.LA(1)==SCOPE) and (_tokenSet_17.member(self.LA(2))) and (self.qualifiedItemIsOneOf(qiType|qiCtor))):
                pass
                s=self.qualified_type()
                if not self.inputState.guessing:
                    ts.append(s)
            elif ((self.LA(1) >= LITERAL_char and self.LA(1) <= LITERAL___declspec)):
                pass
                _cnt129= 0
                while True:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_char]:
                        pass
                        self.match(LITERAL_char)
                        if not self.inputState.guessing:
                            ts.append("char")
                    elif la1 and la1 in [LITERAL_wchar_t]:
                        pass
                        self.match(LITERAL_wchar_t)
                        if not self.inputState.guessing:
                            ts.append("wchar_t")
                    elif la1 and la1 in [LITERAL_bool]:
                        pass
                        self.match(LITERAL_bool)
                        if not self.inputState.guessing:
                            ts.append("bool")
                    elif la1 and la1 in [LITERAL_short]:
                        pass
                        self.match(LITERAL_short)
                        if not self.inputState.guessing:
                            ts.append("short")
                    elif la1 and la1 in [LITERAL_int]:
                        pass
                        self.match(LITERAL_int)
                        if not self.inputState.guessing:
                            ts.append("int")
                    elif la1 and la1 in [44,45]:
                        pass
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [44]:
                            pass
                            self.match(44)
                        elif la1 and la1 in [45]:
                            pass
                            self.match(45)
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        if not self.inputState.guessing:
                            ts.append("long")
                    elif la1 and la1 in [46]:
                        pass
                        self.match(46)
                        if not self.inputState.guessing:
                            ts.append("long")
                    elif la1 and la1 in [LITERAL_long]:
                        pass
                        self.match(LITERAL_long)
                        if not self.inputState.guessing:
                            ts.append("long")
                    elif la1 and la1 in [LITERAL_signed]:
                        pass
                        self.match(LITERAL_signed)
                        if not self.inputState.guessing:
                            ts.append("signed")
                    elif la1 and la1 in [LITERAL_unsigned]:
                        pass
                        self.match(LITERAL_unsigned)
                        if not self.inputState.guessing:
                            ts.append("unsigned")
                    elif la1 and la1 in [LITERAL_float]:
                        pass
                        self.match(LITERAL_float)
                        if not self.inputState.guessing:
                            ts.append("float")
                    elif la1 and la1 in [LITERAL_double]:
                        pass
                        self.match(LITERAL_double)
                        if not self.inputState.guessing:
                            ts.append("double")
                    elif la1 and la1 in [LITERAL_void]:
                        pass
                        self.match(LITERAL_void)
                        if not self.inputState.guessing:
                            ts.append("void")
                    elif la1 and la1 in [LITERAL__declspec,LITERAL___declspec]:
                        pass
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LITERAL__declspec]:
                            pass
                            self.match(LITERAL__declspec)
                        elif la1 and la1 in [LITERAL___declspec]:
                            pass
                            self.match(LITERAL___declspec)
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.match(LPAREN)
                        self.match(ID)
                        self.match(RPAREN)
                    else:
                            break
                        
                    _cnt129 += 1
                if _cnt129 < 1:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            else:
                synPredMatched131 = False
                if (self.LA(1)==ID or self.LA(1)==SCOPE) and (_tokenSet_17.member(self.LA(2))):
                    _m131 = self.mark()
                    synPredMatched131 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.qualified_type()
                        self.qualified_id()
                    except antlr.RecognitionException, pe:
                        synPredMatched131 = False
                    self.rewind(_m131)
                    self.inputState.guessing -= 1
                if synPredMatched131:
                    pass
                    s=self.qualified_type()
                    if not self.inputState.guessing:
                        ts.append("typeid")
                    if not self.inputState.guessing:
                        print("simple_type_specifier third option entered - %s" % (s))
                    if not self.inputState.guessing:
                        ts.append("STS unfinished 2")
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.autonode(None, ts); node.set_result(' '.join(ts))
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return node
    
    def class_specifier(self,
        ds
    ):    
        node = None
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_class]:
                pass
                self.match(LITERAL_class)
                if not self.inputState.guessing:
                    ts = "class"
            elif la1 and la1 in [LITERAL_struct]:
                pass
                self.match(LITERAL_struct)
                if not self.inputState.guessing:
                    ts = "struct"
            elif la1 and la1 in [LITERAL_union]:
                pass
                self.match(LITERAL_union)
                if not self.inputState.guessing:
                    ts = "union"
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,SCOPE]:
                pass
                id=self.qualified_id()
                if not self.inputState.guessing:
                    bases = None
                if (self.LA(1)==LCURLY or self.LA(1)==COLON) and (_tokenSet_43.member(self.LA(2))):
                    pass
                    if not self.inputState.guessing:
                        saveClass = self.enclosingClass
                        self.enclosingClass = id
                    if not self.inputState.guessing:
                        bases = []
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [COLON]:
                        pass
                        bases=self.base_clause()
                    elif la1 and la1 in [LCURLY]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(LCURLY)
                    if not self.inputState.guessing:
                        self.beginClassDefinition(ts, id)
                    if not self.inputState.guessing:
                        members = self.node("members")
                    while True:
                        if (_tokenSet_54.member(self.LA(1))):
                            pass
                            md=self.member_declaration()
                            if not self.inputState.guessing:
                                members.add_child(md)
                        else:
                            break
                        
                    if not self.inputState.guessing:
                        self.endClassDefinition()
                    self.match(RCURLY)
                    if not self.inputState.guessing:
                        node = self.node(ts, bases + [members], id)
                    if not self.inputState.guessing:
                        self.enclosingClass = saveClass
                elif (_tokenSet_17.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                    pass
                    if not self.inputState.guessing:
                        node = self.node(ts, [], id)
                    if not self.inputState.guessing:
                        self.classForwardDeclaration(ts, ds, id)
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            elif la1 and la1 in [LCURLY]:
                pass
                self.match(LCURLY)
                if not self.inputState.guessing:
                    saveClass = self.enclosingClass
                    self.enclosingClass = "__anonymous"
                if not self.inputState.guessing:
                    self.beginClassDefinition(ts, "anonymous")
                if not self.inputState.guessing:
                    members = self.node("members")
                while True:
                    if (_tokenSet_54.member(self.LA(1))):
                        pass
                        md=self.member_declaration()
                        if not self.inputState.guessing:
                            members.add_child(md)
                    else:
                        break
                    
                if not self.inputState.guessing:
                    self.endClassDefinition()
                if not self.inputState.guessing:
                    node = self.node(ts, [members], None)
                self.match(RCURLY)
                if not self.inputState.guessing:
                    self.enclosingClass = saveClass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return node
    
    def qualified_type(self):    
        q = None
        
        id = None
        try:      ## for error handling
            pass
            s=self.scope_override()
            id = self.LT(1)
            self.match(ID)
            if (self.LA(1)==LESSTHAN) and (_tokenSet_35.member(self.LA(2))):
                pass
                self.match(LESSTHAN)
                tal=self.template_argument_list()
                self.match(GREATERTHAN)
            elif (_tokenSet_36.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                pass
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
            if not self.inputState.guessing:
                #printf("qualified_type entered\n");
                q = s + id.getText()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_36)
            else:
                raise ex
        
        return q
    
    def template_argument_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            ta=self.template_argument()
            if not self.inputState.guessing:
                node = self.autonode(ta)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    ta=self.template_argument()
                    if not self.inputState.guessing:
                        node.add_child(ta)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_55)
            else:
                raise ex
        
        return node
    
    def base_clause(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(COLON)
            bs=self.base_specifier()
            if not self.inputState.guessing:
                bsl = bs
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    bs=self.base_specifier()
                    if not self.inputState.guessing:
                        bsl.append(bs)
                else:
                    break
                
            if not self.inputState.guessing:
                node = self.autonode(None, bsl)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_56)
            else:
                raise ex
        
        return node
    
    def enumerator_list(self):    
        
        try:      ## for error handling
            pass
            self.enumerator()
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.enumerator()
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_57)
            else:
                raise ex
        
    
    def enumerator(self):    
        
        id = None
        try:      ## for error handling
            pass
            id = self.LT(1)
            self.match(ID)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ASSIGNEQUAL]:
                pass
                self.match(ASSIGNEQUAL)
                cx=self.constant_expression()
            elif la1 and la1 in [RCURLY,COMMA]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                self.enumElement(id.getText())
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_58)
            else:
                raise ex
        
    
    def constant_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            cs=self.conditional_expression()
            if not self.inputState.guessing:
                node = checknode(cs)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_59)
            else:
                raise ex
        
        return node
    
    def optor(self):    
        out = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_new]:
                pass
                self.match(LITERAL_new)
                if not self.inputState.guessing:
                    out = "new"
                if (self.LA(1)==LSQUARE) and (self.LA(2)==RSQUARE):
                    pass
                    self.match(LSQUARE)
                    self.match(RSQUARE)
                elif (_tokenSet_60.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            elif la1 and la1 in [LITERAL_delete]:
                pass
                self.match(LITERAL_delete)
                if not self.inputState.guessing:
                    out = "delete"
                if (self.LA(1)==LSQUARE) and (self.LA(2)==RSQUARE):
                    pass
                    self.match(LSQUARE)
                    self.match(RSQUARE)
                elif (_tokenSet_60.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                self.match(RPAREN)
                if not self.inputState.guessing:
                    out = "()"
            elif la1 and la1 in [LSQUARE]:
                pass
                self.match(LSQUARE)
                self.match(RSQUARE)
                if not self.inputState.guessing:
                    out = "[]"
            elif la1 and la1 in [LESSTHAN,GREATERTHAN,ASSIGNEQUAL,COMMA,STAR,AMPERSAND,TILDE,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL,OR,AND,BITWISEOR,BITWISEXOR,NOTEQUAL,EQUAL,LESSTHANOREQUALTO,GREATERTHANOREQUALTO,SHIFTLEFT,SHIFTRIGHT,PLUS,MINUS,DIVIDE,MOD,POINTERTOMBR,PLUSPLUS,MINUSMINUS,POINTERTO,NOT]:
                pass
                x=self.optor_simple_tokclass()
                if not self.inputState.guessing:
                    out = x
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_60)
            else:
                raise ex
        
        return out
    
    def typeID(self):    
        
        try:      ## for error handling
            if not self.isTypeName(self.LT(1).getText()):
                raise SemanticException("self.isTypeName(self.LT(1).getText())")
            pass
            self.match(ID)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_1)
            else:
                raise ex
        
    
    def init_declarator(self):    
        node = None
        
        try:      ## for error handling
            pass
            d=self.declarator()
            if not self.inputState.guessing:
                node = self.autonode([d])
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ASSIGNEQUAL]:
                pass
                self.match(ASSIGNEQUAL)
                i=self.initializer()
                if not self.inputState.guessing:
                    node.add_child(i); d.set_result(i.result)
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                el=self.expression_list()
                self.match(RPAREN)
                if not self.inputState.guessing:
                    node.add_child(el); d.set_result(el.result)
            elif la1 and la1 in [SEMICOLON,COMMA,LITERAL___attribute__]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_61)
            else:
                raise ex
        
        return node
    
    def declarator(self):    
        node = None
        
        try:      ## for error handling
            synPredMatched202 = False
            if (_tokenSet_23.member(self.LA(1))) and (_tokenSet_62.member(self.LA(2))):
                _m202 = self.mark()
                synPredMatched202 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.ptr_operator()
                except antlr.RecognitionException, pe:
                    synPredMatched202 = False
                self.rewind(_m202)
                self.inputState.guessing -= 1
            if synPredMatched202:
                pass
                p=self.ptr_operator()
                d=self.declarator()
                if not self.inputState.guessing:
                    node = self.autonode([d], p)
            elif (_tokenSet_63.member(self.LA(1))) and (_tokenSet_64.member(self.LA(2))):
                pass
                d=self.direct_declarator()
                if not self.inputState.guessing:
                    node = d
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_65)
            else:
                raise ex
        
        return node
    
    def initializer(self):    
        node = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY]:
                pass
                self.match(LCURLY)
                i1=self.initializer()
                if not self.inputState.guessing:
                    node = self.autonode([i1])
                while True:
                    if (self.LA(1)==COMMA):
                        pass
                        self.match(COMMA)
                        i2=self.initializer()
                        if not self.inputState.guessing:
                            node.add_child(i2)
                    else:
                        break
                    
                self.match(RCURLY)
            elif la1 and la1 in [DOT]:
                pass
                d2=self.c99_designator()
                i4=self.initializer()
                if not self.inputState.guessing:
                    node = self.autonode([d2, i4])
            else:
                if (_tokenSet_66.member(self.LA(1))) and (_tokenSet_67.member(self.LA(2))):
                    pass
                    rx=self.remainder_expression()
                    if not self.inputState.guessing:
                        node = checknode(rx)
                elif (self.LA(1)==ID) and (self.LA(2)==COLON):
                    pass
                    d1=self.gcc_designator()
                    i3=self.initializer()
                    if not self.inputState.guessing:
                        node = self.autonode([d1, i3])
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_68)
            else:
                raise ex
        
        return node
    
    def expression_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.assignment_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    x=self.assignment_expression()
                    if not self.inputState.guessing:
                        node.add_child(x)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_53)
            else:
                raise ex
        
        return node
    
    def remainder_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            synPredMatched365 = False
            if (_tokenSet_66.member(self.LA(1))) and (_tokenSet_69.member(self.LA(2))):
                _m365 = self.mark()
                synPredMatched365 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.conditional_expression()
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [COMMA]:
                        pass
                        self.match(COMMA)
                    elif la1 and la1 in [SEMICOLON]:
                        pass
                        self.match(SEMICOLON)
                    elif la1 and la1 in [RPAREN]:
                        pass
                        self.match(RPAREN)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                except antlr.RecognitionException, pe:
                    synPredMatched365 = False
                self.rewind(_m365)
                self.inputState.guessing -= 1
            if synPredMatched365:
                pass
                if not self.inputState.guessing:
                    self.assign_stmt_RHS_found += 1
                x=self.assignment_expression()
                if not self.inputState.guessing:
                    node = checknode(x)
                if not self.inputState.guessing:
                    if self.assign_stmt_RHS_found > 0:
                       self.assign_stmt_RHS_found -= 1
                    else:
                       print "%d warning Error in assign_stmt_RHS_found = %d" % (self.LT(1).getLine(), self.assign_stmt_RHS_found);
            elif (_tokenSet_66.member(self.LA(1))) and (_tokenSet_69.member(self.LA(2))):
                pass
                x=self.assignment_expression()
                if not self.inputState.guessing:
                    node = checknode(x)
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_70)
            else:
                raise ex
        
        return node
    
    def gcc_designator(self):    
        node = None
        
        id = None
        try:      ## for error handling
            pass
            id = self.LT(1)
            self.match(ID)
            self.match(COLON)
            if not self.inputState.guessing:
                node = self.node("designator", None, id.getText())
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_71)
            else:
                raise ex
        
        return node
    
    def c99_designator(self):    
        node = None
        
        id = None
        try:      ## for error handling
            pass
            self.match(DOT)
            id = self.LT(1)
            self.match(ID)
            self.match(EQUALS)
            if not self.inputState.guessing:
                node = self.node("designator", None, id.getText())
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_71)
            else:
                raise ex
        
        return node
    
    def base_specifier(self):    
        bsl = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                bsl = []
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_virtual]:
                pass
                self.match(LITERAL_virtual)
                if not self.inputState.guessing:
                    bsl.append("virtual")
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_public,LITERAL_protected,LITERAL_private]:
                    pass
                    as=self.access_specifier()
                    if not self.inputState.guessing:
                        bsl.append(as)
                elif la1 and la1 in [ID,SCOPE]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                qt=self.qualified_type()
                if not self.inputState.guessing:
                    bsl.append(qt)
            elif la1 and la1 in [LITERAL_public,LITERAL_protected,LITERAL_private]:
                pass
                as=self.access_specifier()
                if not self.inputState.guessing:
                    bsl.append(as)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_virtual]:
                    pass
                    self.match(LITERAL_virtual)
                    if not self.inputState.guessing:
                        bsl.append("virtual")
                elif la1 and la1 in [ID,SCOPE]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                qt=self.qualified_type()
                if not self.inputState.guessing:
                    bsl.append(qt)
            elif la1 and la1 in [ID,SCOPE]:
                pass
                qt=self.qualified_type()
                if not self.inputState.guessing:
                    bsl.append(qt)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_72)
            else:
                raise ex
        
        return bsl
    
    def member_declarator(self):    
        node = None
        
        id = None
        try:      ## for error handling
            synPredMatched186 = False
            if (self.LA(1)==ID or self.LA(1)==COLON) and (_tokenSet_73.member(self.LA(2))):
                _m186 = self.mark()
                synPredMatched186 = True
                self.inputState.guessing += 1
                try:
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [ID]:
                        pass
                        self.match(ID)
                    elif la1 and la1 in [COLON]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(COLON)
                    self.constant_expression()
                except antlr.RecognitionException, pe:
                    synPredMatched186 = False
                self.rewind(_m186)
                self.inputState.guessing -= 1
            if synPredMatched186:
                pass
                if not self.inputState.guessing:
                    node = self.node("member_declarator_bitfield")
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID]:
                    pass
                    id = self.LT(1)
                    self.match(ID)
                    if not self.inputState.guessing:
                        node.set_leaf(id.getText())
                elif la1 and la1 in [COLON]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(COLON)
                c=self.constant_expression()
                if not self.inputState.guessing:
                    node.add_child(c)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ASSIGNEQUAL]:
                    pass
                    self.match(ASSIGNEQUAL)
                    self.match(OCTALINT)
                    if not self.inputState.guessing:
                        node.add_attribute("purevirtual")
                elif la1 and la1 in [SEMICOLON,COMMA]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            elif (_tokenSet_74.member(self.LA(1))) and (_tokenSet_75.member(self.LA(2))):
                pass
                d=self.declarator()
                if not self.inputState.guessing:
                    node = self.autonode([d])
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ASSIGNEQUAL]:
                    pass
                    self.match(ASSIGNEQUAL)
                    self.match(OCTALINT)
                    if not self.inputState.guessing:
                        node.set_leaf(0)
                elif la1 and la1 in [SEMICOLON,COMMA]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_76)
            else:
                raise ex
        
        return node
    
    def template_parameter_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                self.beginTemplateParameterList()
            if not self.inputState.guessing:
                node = self.autonode()
            tp=self.template_parameter()
            if not self.inputState.guessing:
                node.add_child(tp)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    tp=self.template_parameter()
                    if not self.inputState.guessing:
                        node.add_child(tp)
                else:
                    break
                
            if not self.inputState.guessing:
                self.endTemplateParameterList()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_55)
            else:
                raise ex
        
        return node
    
    def parameter_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            pdl=self.parameter_declaration_list()
            if not self.inputState.guessing:
                node = self.autonode([pdl])
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ELLIPSIS]:
                pass
                self.match(ELLIPSIS)
                if not self.inputState.guessing:
                    node.set_leaf("...")
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_53)
            else:
                raise ex
        
        return node
    
    def exception_specification(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(LITERAL_throw)
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,RPAREN,SCOPE]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID,SCOPE]:
                    pass
                    so=self.scope_override()
                    self.match(ID)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [COMMA]:
                        pass
                        self.match(COMMA)
                        so=self.scope_override()
                        self.match(ID)
                    elif la1 and la1 in [RPAREN]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            elif la1 and la1 in [ELLIPSIS]:
                pass
                self.match(ELLIPSIS)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_77)
            else:
                raise ex
        
        return node
    
    def cv_qualifier_seq(self):    
        cvs = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                cvs = ""
            while True:
                if (_tokenSet_50.member(self.LA(1))):
                    pass
                    tq=self.type_qualifier()
                    if not self.inputState.guessing:
                        cvs += tq
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_78)
            else:
                raise ex
        
        return cvs
    
    def ptr_operator(self):    
        oper = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                oper="UNKNOWN"
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [AMPERSAND]:
                pass
                self.match(AMPERSAND)
                if not self.inputState.guessing:
                    oper = "&"
                if not self.inputState.guessing:
                    self.is_address = True
            elif la1 and la1 in [LITERAL__cdecl,LITERAL___cdecl]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL__cdecl]:
                    pass
                    self.match(LITERAL__cdecl)
                elif la1 and la1 in [LITERAL___cdecl]:
                    pass
                    self.match(LITERAL___cdecl)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    oper = "_cdecl"
            elif la1 and la1 in [LITERAL__near,LITERAL___near]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL__near]:
                    pass
                    self.match(LITERAL__near)
                elif la1 and la1 in [LITERAL___near]:
                    pass
                    self.match(LITERAL___near)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    oper = "_near"
            elif la1 and la1 in [LITERAL__far,LITERAL___far]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL__far]:
                    pass
                    self.match(LITERAL__far)
                elif la1 and la1 in [LITERAL___far]:
                    pass
                    self.match(LITERAL___far)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    oper = "_far"
            elif la1 and la1 in [LITERAL___interrupt]:
                pass
                self.match(LITERAL___interrupt)
                if not self.inputState.guessing:
                    oper = "__interrupt"
            elif la1 and la1 in [LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_pascal]:
                    pass
                    self.match(LITERAL_pascal)
                elif la1 and la1 in [LITERAL__pascal]:
                    pass
                    self.match(LITERAL__pascal)
                elif la1 and la1 in [LITERAL___pascal]:
                    pass
                    self.match(LITERAL___pascal)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    oper = "pascal"
            elif la1 and la1 in [LITERAL__stdcall,LITERAL___stdcall]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL__stdcall]:
                    pass
                    self.match(LITERAL__stdcall)
                elif la1 and la1 in [LITERAL___stdcall]:
                    pass
                    self.match(LITERAL___stdcall)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    oper = "_stdcall"
            elif la1 and la1 in [ID,STAR,SCOPE]:
                pass
                ptm=self.ptr_to_member()
                if not self.inputState.guessing:
                    oper = ptm
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return oper
    
    def declarator_suffixes(self):    
        node = None
        
        try:      ## for error handling
            pass
            if (self.LA(1)==LSQUARE):
                pass
                _cnt223= 0
                while True:
                    if (self.LA(1)==LSQUARE) and (_tokenSet_51.member(self.LA(2))):
                        pass
                        self.match(LSQUARE)
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                            pass
                            cx=self.constant_expression()
                        elif la1 and la1 in [RSQUARE]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.match(RSQUARE)
                    else:
                        break
                    
                    _cnt223 += 1
                if _cnt223 < 1:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                if not self.inputState.guessing:
                    self.declaratorArray()
            elif ((self.LA(1)==LPAREN) and ((not ((self.LA(1)==LPAREN) and (self.LA(2)==ID)) or (self.qualifiedItemIsOneOf(qiType|qiCtor,1))))):
                pass
                self.match(LPAREN)
                if not self.inputState.guessing:
                    self.declaratorParameterList(0)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                    pass
                    pl=self.parameter_list()
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(RPAREN)
                if not self.inputState.guessing:
                    self.declaratorEndParameterList(0)
                while True:
                    if (_tokenSet_50.member(self.LA(1))):
                        pass
                        tq=self.type_qualifier()
                    else:
                        break
                    
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_throw]:
                    pass
                    es=self.exception_specification()
                elif la1 and la1 in [LESSTHAN,GREATERTHAN,ID,SEMICOLON,RCURLY,ASSIGNEQUAL,COLON,COMMA,LITERAL__stdcall,LITERAL___stdcall,LITERAL___attribute__,LPAREN,RPAREN,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,LSQUARE,RSQUARE,TILDE,ELLIPSIS,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL,QUESTIONMARK,OR,AND,BITWISEOR,BITWISEXOR,NOTEQUAL,EQUAL,LESSTHANOREQUALTO,GREATERTHANOREQUALTO,SHIFTLEFT,SHIFTRIGHT,PLUS,MINUS,DIVIDE,MOD,DOTMBR,POINTERTOMBR,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return node
    
    def function_direct_declarator(self,
        definition
    ):    
        q = None
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                q=self.qualified_id()
                if not self.inputState.guessing:
                    self.declaratorID(q,qiFun)
                self.match(RPAREN)
            elif la1 and la1 in [ID,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,SCOPE]:
                pass
                q=self.qualified_id()
                if not self.inputState.guessing:
                    self.declaratorID(q,qiFun)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                if definition:
                   self.myCode_function_direct_declarator(q)
            self.match(LPAREN)
            if not self.inputState.guessing:
                self.functionParameterList()
                if not self.K_and_R:
                   self.in_parameter_list = True
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                pass
                pl=self.parameter_list()
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                if not self.K_and_R:
                   self.in_parameter_list = False
                else:
                   self.in_parameter_list = True
            self.match(RPAREN)
            while True:
                if (_tokenSet_50.member(self.LA(1))) and (_tokenSet_79.member(self.LA(2))):
                    pass
                    tq=self.type_qualifier()
                else:
                    break
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ASSIGNEQUAL]:
                pass
                self.match(ASSIGNEQUAL)
                self.match(OCTALINT)
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LCURLY,SEMICOLON,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,LITERAL_throw,LITERAL_using,SCOPE]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                self.functionEndParameterList(definition)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_throw]:
                pass
                es=self.exception_specification()
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LCURLY,SEMICOLON,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,LITERAL_using,SCOPE]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_27)
            else:
                raise ex
        
        return q
    
    def ctor_head(self):    
        node = None
        
        try:      ## for error handling
            pass
            cds=self.ctor_decl_spec()
            cd=self.ctor_declarator(1)
            if not self.inputState.guessing:
                node = self.autonode([cds, cd])
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_80)
            else:
                raise ex
        
        return node
    
    def ctor_body(self):    
        node = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                node = self.autonode()
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [COLON]:
                pass
                ci=self.ctor_initializer()
                if not self.inputState.guessing:
                    node.add_child(ci)
            elif la1 and la1 in [LCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            cs=self.compound_statement()
            if not self.inputState.guessing:
                node.add_child(ci)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        return node
    
    def qualified_ctor_id(self):    
        q = None
        
        id = None
        qitem = ""
        try:      ## for error handling
            pass
            so=self.scope_override()
            if not self.inputState.guessing:
                qitem = so
            id = self.LT(1)
            self.match(ID)
            if not self.inputState.guessing:
                qitem += id.getText(); q = qitem
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_81)
            else:
                raise ex
        
        return q
    
    def ctor_initializer(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(COLON)
            self.superclass_init()
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.superclass_init()
                else:
                    break
                
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_56)
            else:
                raise ex
        
        return node
    
    def superclass_init(self):    
        
        char *q;
        try:      ## for error handling
            pass
            q=self.qualified_id()
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                pass
                el=self.expression_list()
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_72)
            else:
                raise ex
        
    
    def dtor_decl_spec(self):    
        sl = None
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                sl = []
            while True:
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_inline,LITERAL__inline,LITERAL___inline]:
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_inline]:
                        pass
                        self.match(LITERAL_inline)
                    elif la1 and la1 in [LITERAL__inline]:
                        pass
                        self.match(LITERAL__inline)
                    elif la1 and la1 in [LITERAL___inline]:
                        pass
                        self.match(LITERAL___inline)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    if not self.inputState.guessing:
                        sl.append("inline")
                elif la1 and la1 in [LITERAL_virtual]:
                    pass
                    self.match(LITERAL_virtual)
                    if not self.inputState.guessing:
                        sl.append("virtual")
                else:
                        break
                    
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_82)
            else:
                raise ex
        
        return sl
    
    def dtor_declarator(self,
        definition
    ):    
        node = None
        
        try:      ## for error handling
            pass
            s=self.scope_override()
            self.match(TILDE)
            self.match(ID)
            if not self.inputState.guessing:
                self.declaratorParameterList(definition)
            self.match(LPAREN)
            self.match(RPAREN)
            if not self.inputState.guessing:
                self.declaratorEndParameterList(definition)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_throw]:
                pass
                es=self.exception_specification()
            elif la1 and la1 in [LCURLY,SEMICOLON]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.autonode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        return node
    
    def parameter_declaration_list(self):    
        node = None
        
        try:      ## for error handling
            pass
            pass
            self.parameter_declaration()
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.parameter_declaration()
                else:
                    break
                
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_83)
            else:
                raise ex
        
        return node
    
    def parameter_declaration(self):    
        
        try:      ## for error handling
            pass
            if not self.inputState.guessing:
                self.beginParameterDeclaration()
            if ((_tokenSet_13.member(self.LA(1))) and (_tokenSet_84.member(self.LA(2))) and (not ((self.LA(1)==SCOPE) and (self.LA(2)==STAR or self.LA(2)==OPERATOR)) and ( not (self.LA(1)==SCOPE or self.LA(1)==ID) or self.qualifiedItemIsOneOf(qiType|qiCtor) ))):
                pass
                ds=self.declaration_specifiers()
                synPredMatched273 = False
                if (_tokenSet_74.member(self.LA(1))) and (_tokenSet_85.member(self.LA(2))):
                    _m273 = self.mark()
                    synPredMatched273 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.declarator()
                    except antlr.RecognitionException, pe:
                        synPredMatched273 = False
                    self.rewind(_m273)
                    self.inputState.guessing -= 1
                if synPredMatched273:
                    pass
                    d=self.declarator()
                elif (_tokenSet_86.member(self.LA(1))) and (_tokenSet_87.member(self.LA(2))):
                    pass
                    ad=self.abstract_declarator()
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            else:
                synPredMatched275 = False
                if (_tokenSet_74.member(self.LA(1))) and (_tokenSet_85.member(self.LA(2))):
                    _m275 = self.mark()
                    synPredMatched275 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.declarator()
                    except antlr.RecognitionException, pe:
                        synPredMatched275 = False
                    self.rewind(_m275)
                    self.inputState.guessing -= 1
                if synPredMatched275:
                    pass
                    d=self.declarator()
                elif (self.LA(1)==ELLIPSIS):
                    pass
                    self.match(ELLIPSIS)
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ASSIGNEQUAL]:
                pass
                self.match(ASSIGNEQUAL)
                re=self.remainder_expression()
            elif la1 and la1 in [GREATERTHAN,COMMA,RPAREN,ELLIPSIS]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_88)
            else:
                raise ex
        
    
    def abstract_declarator(self):    
        node = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,STAR,AMPERSAND,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                pass
                po=self.ptr_operator()
                ad=self.abstract_declarator()
                if not self.inputState.guessing:
                    node = self.autonode([ad], po); node.set_result(po.result + ad.result)
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                ad2=self.abstract_declarator()
                self.match(RPAREN)
                if not self.inputState.guessing:
                    node = self.autonode([ad2])
                _cnt280= 0
                while True:
                    if (self.LA(1)==LPAREN or self.LA(1)==LSQUARE):
                        pass
                        ads=self.abstract_declarator_suffix()
                        if not self.inputState.guessing:
                            node.add_child(ads)
                    else:
                        break
                    
                    _cnt280 += 1
                if _cnt280 < 1:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                if not self.inputState.guessing:
                    node.set_result(None)
            elif la1 and la1 in [LSQUARE]:
                pass
                if not self.inputState.guessing:
                    node = self.autonode(None, "[]")
                _cnt283= 0
                while True:
                    if (self.LA(1)==LSQUARE):
                        pass
                        self.match(LSQUARE)
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                            pass
                            cx=self.constant_expression()
                            if not self.inputState.guessing:
                                node.add_child(dx)
                        elif la1 and la1 in [RSQUARE]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.match(RSQUARE)
                        if not self.inputState.guessing:
                            self.declaratorArray()
                    else:
                        break
                    
                    _cnt283 += 1
                if _cnt283 < 1:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                if not self.inputState.guessing:
                    node.set_result(None)
            elif la1 and la1 in [GREATERTHAN,ASSIGNEQUAL,COMMA,RPAREN,ELLIPSIS]:
                pass
                if not self.inputState.guessing:
                    node = self.autonode()
                if not self.inputState.guessing:
                    node.set_result("")
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_89)
            else:
                raise ex
        
        return node
    
    def type_name(self):    
        node = None
        
        try:      ## for error handling
            pass
            ds=self.declaration_specifiers()
            ad=self.abstract_declarator()
            if not self.inputState.guessing:
                node = self.autonode([checknode(ds), checknode(ad)]); node.set_result(ds.result + ad.result)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_90)
            else:
                raise ex
        
        return node
    
    def abstract_declarator_suffix(self):    
        node = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LSQUARE]:
                pass
                if not self.inputState.guessing:
                    node = self.autonode(None, "[]")
                self.match(LSQUARE)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                    pass
                    cx=self.constant_expression()
                    if not self.inputState.guessing:
                        node.add_child(cx)
                elif la1 and la1 in [RSQUARE]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(RSQUARE)
                if not self.inputState.guessing:
                    self.declaratorArray()
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                if not self.inputState.guessing:
                    node = self.autonode()
                if not self.inputState.guessing:
                    self.declaratorParameterList(0);
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LPAREN,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,STAR,AMPERSAND,TILDE,ELLIPSIS,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                    pass
                    pl=self.parameter_list()
                    if not self.inputState.guessing:
                        node.add_child(pl)
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(RPAREN)
                cvs=self.cv_qualifier_seq()
                if not self.inputState.guessing:
                    node.set_leaf(["()", cvs])
                if not self.inputState.guessing:
                    self.declaratorEndParameterList(0)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_throw]:
                    pass
                    es=self.exception_specification()
                    if not self.inputState.guessing:
                        node.add_child(es)
                elif la1 and la1 in [GREATERTHAN,ASSIGNEQUAL,COMMA,LPAREN,RPAREN,LSQUARE,ELLIPSIS]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_91)
            else:
                raise ex
        
        return node
    
    def template_parameter(self):    
        node = None
        
        id = None
        try:      ## for error handling
            pass
            if (self.LA(1)==LITERAL_typename or self.LA(1)==LITERAL_class) and (_tokenSet_92.member(self.LA(2))):
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_class]:
                    pass
                    self.match(LITERAL_class)
                elif la1 and la1 in [LITERAL_typename]:
                    pass
                    self.match(LITERAL_typename)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID]:
                    pass
                    id = self.LT(1)
                    self.match(ID)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [ASSIGNEQUAL]:
                        pass
                        self.match(ASSIGNEQUAL)
                        self.assigned_type_name()
                    elif la1 and la1 in [GREATERTHAN,COMMA]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                elif la1 and la1 in [GREATERTHAN,COMMA]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    self.templateTypeParameter(id.getText())
            elif (_tokenSet_93.member(self.LA(1))) and (_tokenSet_11.member(self.LA(2))):
                pass
                self.parameter_declaration()
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_94)
            else:
                raise ex
        
        return node
    
    def assigned_type_name(self):    
        
        try:      ## for error handling
            pass
            if (self.LA(1)==ID or self.LA(1)==SCOPE) and (_tokenSet_95.member(self.LA(2))):
                pass
                s=self.qualified_type()
                ad=self.abstract_declarator()
            elif (_tokenSet_96.member(self.LA(1))) and (_tokenSet_97.member(self.LA(2))):
                pass
                ts=self.simple_type_specifier()
                ad=self.abstract_declarator()
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_94)
            else:
                raise ex
        
    
    def template_id(self):    
        
        try:      ## for error handling
            pass
            self.match(ID)
            self.match(LESSTHAN)
            tal=self.template_argument_list()
            self.match(GREATERTHAN)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_1)
            else:
                raise ex
        
    
    def template_argument(self):    
        node = None
        
        try:      ## for error handling
            if ((_tokenSet_13.member(self.LA(1))) and (_tokenSet_98.member(self.LA(2))) and (( not (self.LA(1)==SCOPE or self.LA(1)==ID) or self.qualifiedItemIsOneOf(qiType|qiCtor) ))):
                pass
                tn=self.type_name()
            elif (_tokenSet_66.member(self.LA(1))) and (_tokenSet_99.member(self.LA(2))):
                pass
                sx=self.shift_expression()
                if not self.inputState.guessing:
                    node = self.unfinishednode()
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_94)
            else:
                raise ex
        
        return node
    
    def shift_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.additive_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==SHIFTLEFT or self.LA(1)==SHIFTRIGHT):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [SHIFTLEFT]:
                        pass
                        self.match(SHIFTLEFT)
                        if not self.inputState.guessing:
                            leaf = "<<"
                    elif la1 and la1 in [SHIFTRIGHT]:
                        pass
                        self.match(SHIFTRIGHT)
                        if not self.inputState.guessing:
                            leaf = ">>"
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    x=self.additive_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, leaf)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_100)
            else:
                raise ex
        
        return node
    
    def statement_list(self):    
        node = None
        
        accum = []
        try:      ## for error handling
            pass
            _cnt310= 0
            while True:
                if (_tokenSet_101.member(self.LA(1))):
                    pass
                    s=self.statement()
                    if not self.inputState.guessing:
                        accum.append(s)
                else:
                    break
                
                _cnt310 += 1
            if _cnt310 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            if not self.inputState.guessing:
                node = self.autonode(accum)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_57)
            else:
                raise ex
        
        return node
    
    def statement(self):    
        node = None
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_case]:
                pass
                self.case_statement()
                if not self.inputState.guessing:
                    node = self.unfinishednode("statement_case")
            elif la1 and la1 in [LITERAL_default]:
                pass
                self.default_statement()
                if not self.inputState.guessing:
                    node = self.unfinishednode("statement_default")
            elif la1 and la1 in [LCURLY]:
                pass
                compstat=self.compound_statement()
                if not self.inputState.guessing:
                    node = checknode(compstat)
            elif la1 and la1 in [LITERAL_if,LITERAL_switch]:
                pass
                sstat=self.selection_statement()
                if not self.inputState.guessing:
                    node = checknode(sstat)
            elif la1 and la1 in [LITERAL_while,LITERAL_do,LITERAL_for]:
                pass
                iterstat=self.iteration_statement()
                if not self.inputState.guessing:
                    node = checknode(iterstat)
            elif la1 and la1 in [LITERAL_goto,LITERAL_continue,LITERAL_break,LITERAL_return]:
                pass
                jumpstat=self.jump_statement()
                if not self.inputState.guessing:
                    node = checknode(jumpstat)
            elif la1 and la1 in [SEMICOLON]:
                pass
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node = self.blanknode()
            elif la1 and la1 in [LITERAL_try]:
                pass
                self.try_block()
                if not self.inputState.guessing:
                    node = self.unfinishednode("statement_try")
            elif la1 and la1 in [LITERAL_throw]:
                pass
                self.throw_statement()
                if not self.inputState.guessing:
                    node = self.unfinishednode("statement_throw")
            elif la1 and la1 in [LITERAL__asm,LITERAL___asm,LITERAL___asm__,LITERAL_asm]:
                pass
                self.asm_block()
                if not self.inputState.guessing:
                    node = self.unfinishednode("statement_asm_block")
            else:
                synPredMatched314 = False
                if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                    _m314 = self.mark()
                    synPredMatched314 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.declaration()
                    except antlr.RecognitionException, pe:
                        synPredMatched314 = False
                    self.rewind(_m314)
                    self.inputState.guessing -= 1
                if synPredMatched314:
                    pass
                    d=self.declaration()
                    if not self.inputState.guessing:
                        node = self.autonode([d])
                elif (self.LA(1)==ID) and (self.LA(2)==COLON):
                    pass
                    self.labeled_statement()
                    if not self.inputState.guessing:
                        node = self.unfinishednode("statement_labeled")
                elif (_tokenSet_66.member(self.LA(1))) and (_tokenSet_102.member(self.LA(2))):
                    pass
                    e=self.expression()
                    if not self.inputState.guessing:
                        node = checknode(e)
                    self.match(SEMICOLON)
                    if not self.inputState.guessing:
                        self.end_of_stmt()
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
        return node
    
    def labeled_statement(self):    
        
        try:      ## for error handling
            pass
            self.match(ID)
            self.match(COLON)
            s=self.statement()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def case_statement(self):    
        
        try:      ## for error handling
            pass
            self.match(LITERAL_case)
            cx=self.constant_expression()
            self.match(COLON)
            s=self.statement()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def default_statement(self):    
        
        try:      ## for error handling
            pass
            self.match(LITERAL_default)
            self.match(COLON)
            s=self.statement()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.assignment_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    x=self.assignment_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, ",")
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_104)
            else:
                raise ex
        
        return node
    
    def selection_statement(self):    
        node = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_if]:
                pass
                self.match(LITERAL_if)
                self.match(LPAREN)
                x1=self.expression()
                self.match(RPAREN)
                s1=self.statement()
                if not self.inputState.guessing:
                    node = self.autonode([x1, s1], "if")
                if (self.LA(1)==LITERAL_else) and (_tokenSet_101.member(self.LA(2))):
                    pass
                    self.match(LITERAL_else)
                    s2=self.statement()
                    if not self.inputState.guessing:
                        node.add_child(s2)
                elif (_tokenSet_103.member(self.LA(1))) and (_tokenSet_105.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            elif la1 and la1 in [LITERAL_switch]:
                pass
                self.match(LITERAL_switch)
                self.match(LPAREN)
                x3=self.expression()
                self.match(RPAREN)
                s3=self.statement()
                if not self.inputState.guessing:
                    node = self.autonode([x3, x4], "switch")
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
        return node
    
    def iteration_statement(self):    
        node = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_while]:
                pass
                self.match(LITERAL_while)
                self.match(LPAREN)
                x1=self.expression()
                self.match(RPAREN)
                s1=self.statement()
                if not self.inputState.guessing:
                    node = self.autonode([x1, s1], "while")
            elif la1 and la1 in [LITERAL_do]:
                pass
                self.match(LITERAL_do)
                s2=self.statement()
                self.match(LITERAL_while)
                self.match(LPAREN)
                x2=self.expression()
                self.match(RPAREN)
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node = self.autonode([s2, x2], "do")
            elif la1 and la1 in [LITERAL_for]:
                pass
                self.match(LITERAL_for)
                self.match(LPAREN)
                synPredMatched325 = False
                if (_tokenSet_2.member(self.LA(1))) and (_tokenSet_3.member(self.LA(2))):
                    _m325 = self.mark()
                    synPredMatched325 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.declaration()
                    except antlr.RecognitionException, pe:
                        synPredMatched325 = False
                    self.rewind(_m325)
                    self.inputState.guessing -= 1
                if synPredMatched325:
                    pass
                    d1=self.declaration()
                    if not self.inputState.guessing:
                        node = self.autonode([d1], "for")
                elif (_tokenSet_66.member(self.LA(1))) and (_tokenSet_102.member(self.LA(2))):
                    pass
                    x3=self.expression()
                    self.match(SEMICOLON)
                    if not self.inputState.guessing:
                        self.end_of_stmt()
                    if not self.inputState.guessing:
                        node = self.autonode([x3], "for")
                elif (self.LA(1)==SEMICOLON):
                    pass
                    self.match(SEMICOLON)
                    if not self.inputState.guessing:
                        self.end_of_stmt()
                    if not self.inputState.guessing:
                        node = self.autonode([self.blanknode()], "for")
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
                if not self.inputState.guessing:
                    x4 = self.blanknode()
                if not self.inputState.guessing:
                    x5 = self.blanknode()
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                    pass
                    x4=self.expression()
                elif la1 and la1 in [SEMICOLON]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                    pass
                    x5=self.expression()
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                if not self.inputState.guessing:
                    node.add_child(x4)
                if not self.inputState.guessing:
                    node.add_child(x5)
                self.match(RPAREN)
                s3=self.statement()
                if not self.inputState.guessing:
                    node.add_child(s3)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
        return node
    
    def jump_statement(self):    
        node = None
        
        gotoid = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_goto]:
                pass
                self.match(LITERAL_goto)
                gotoid = self.LT(1)
                self.match(ID)
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node = self.node("jump_goto", None, gotoid)
            elif la1 and la1 in [LITERAL_continue]:
                pass
                self.match(LITERAL_continue)
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node = self.autonode(None, "continue")
            elif la1 and la1 in [LITERAL_break]:
                pass
                self.match(LITERAL_break)
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.end_of_stmt()
                if not self.inputState.guessing:
                    node = self.autonode(None, "break")
            elif la1 and la1 in [LITERAL_return]:
                pass
                self.match(LITERAL_return)
                if not self.inputState.guessing:
                    self.in_return = True
                x=self.expression()
                self.match(SEMICOLON)
                if not self.inputState.guessing:
                    self.in_return = False
                    self.end_of_stmt() 
                    node = self.autonode([x], "return")
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
        return node
    
    def try_block(self):    
        
        try:      ## for error handling
            pass
            self.match(LITERAL_try)
            compstat=self.compound_statement()
            while True:
                if (self.LA(1)==LITERAL_catch):
                    pass
                    self.handler()
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def throw_statement(self):    
        
        try:      ## for error handling
            pass
            self.match(LITERAL_throw)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                pass
                ax=self.assignment_expression()
            elif la1 and la1 in [SEMICOLON]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(SEMICOLON)
            if not self.inputState.guessing:
                end_of_stmt();
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def asm_block(self):    
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL__asm,LITERAL___asm]:
                pass
                self.std_asm_block()
            elif la1 and la1 in [LITERAL___asm__,LITERAL_asm]:
                pass
                self.gcc_asm_block()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def handler(self):    
        
        try:      ## for error handling
            pass
            self.match(LITERAL_catch)
            if not self.inputState.guessing:
                self.exceptionBeginHandler()
            if not self.inputState.guessing:
                self.declaratorParameterList(1)
            self.match(LPAREN)
            self.exception_declaration()
            self.match(RPAREN)
            if not self.inputState.guessing:
                self.declaratorEndParameterList(1)
            compstat=self.compound_statement()
            if not self.inputState.guessing:
                self.exceptionEndHandler()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_106)
            else:
                raise ex
        
    
    def exception_declaration(self):    
        
        try:      ## for error handling
            pass
            pdl=self.parameter_declaration_list()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_53)
            else:
                raise ex
        
    
    def assignment_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            cx=self.conditional_expression()
            if not self.inputState.guessing:
                node = checknode(cx)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ASSIGNEQUAL,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ASSIGNEQUAL]:
                    pass
                    self.match(ASSIGNEQUAL)
                    if not self.inputState.guessing:
                        leaf="="
                elif la1 and la1 in [TIMESEQUAL]:
                    pass
                    self.match(TIMESEQUAL)
                    if not self.inputState.guessing:
                        leaf="*="
                elif la1 and la1 in [DIVIDEEQUAL]:
                    pass
                    self.match(DIVIDEEQUAL)
                    if not self.inputState.guessing:
                        leaf="/="
                elif la1 and la1 in [MINUSEQUAL]:
                    pass
                    self.match(MINUSEQUAL)
                    if not self.inputState.guessing:
                        leaf="-="
                elif la1 and la1 in [PLUSEQUAL]:
                    pass
                    self.match(PLUSEQUAL)
                    if not self.inputState.guessing:
                        leaf="+="
                elif la1 and la1 in [MODEQUAL]:
                    pass
                    self.match(MODEQUAL)
                    if not self.inputState.guessing:
                        leaf="%="
                elif la1 and la1 in [SHIFTLEFTEQUAL]:
                    pass
                    self.match(SHIFTLEFTEQUAL)
                    if not self.inputState.guessing:
                        leaf="<<="
                elif la1 and la1 in [SHIFTRIGHTEQUAL]:
                    pass
                    self.match(SHIFTRIGHTEQUAL)
                    if not self.inputState.guessing:
                        leaf=">>="
                elif la1 and la1 in [BITWISEANDEQUAL]:
                    pass
                    self.match(BITWISEANDEQUAL)
                    if not self.inputState.guessing:
                        leaf="&="
                elif la1 and la1 in [BITWISEXOREQUAL]:
                    pass
                    self.match(BITWISEXOREQUAL)
                    if not self.inputState.guessing:
                        leaf="^="
                elif la1 and la1 in [BITWISEOREQUAL]:
                    pass
                    self.match(BITWISEOREQUAL)
                    if not self.inputState.guessing:
                        leaf="|="
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                rx=self.remainder_expression()
                if not self.inputState.guessing:
                    node = self.exprnode_acc(node, checknode(rx), leaf)
            elif la1 and la1 in [GREATERTHAN,SEMICOLON,RCURLY,COLON,COMMA,LITERAL___attribute__,RPAREN,RSQUARE,ELLIPSIS]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_70)
            else:
                raise ex
        
        return node
    
    def std_asm_block(self):    
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL__asm]:
                pass
                self.match(LITERAL__asm)
            elif la1 and la1 in [LITERAL___asm]:
                pass
                self.match(LITERAL___asm)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(LCURLY)
            while True:
                if (_tokenSet_107.member(self.LA(1))):
                    pass
                    self.matchNot(RCURLY)
                else:
                    break
                
            self.match(RCURLY)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def gcc_asm_block(self):    
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL___asm__]:
                pass
                self.match(LITERAL___asm__)
            elif la1 and la1 in [LITERAL_asm]:
                pass
                self.match(LITERAL_asm)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_volatile]:
                pass
                self.match(LITERAL_volatile)
            elif la1 and la1 in [LPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(LPAREN)
            self.asm_code()
            self.match(COLON)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [StringLiteral]:
                pass
                self.asm_reg_spec()
            elif la1 and la1 in [COLON]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(COLON)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [StringLiteral]:
                pass
                self.asm_reg_spec()
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_103)
            else:
                raise ex
        
    
    def asm_code(self):    
        
        try:      ## for error handling
            pass
            _cnt351= 0
            while True:
                if (self.LA(1)==StringLiteral):
                    pass
                    self.match(StringLiteral)
                else:
                    break
                
                _cnt351 += 1
            if _cnt351 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_108)
            else:
                raise ex
        
    
    def asm_reg_spec(self):    
        
        try:      ## for error handling
            pass
            self.match(StringLiteral)
            self.match(LPAREN)
            self.match(ID)
            self.match(RPAREN)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.match(StringLiteral)
                    self.match(LPAREN)
                    self.match(ID)
                    self.match(RPAREN)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_109)
            else:
                raise ex
        
    
    def conditional_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            lx=self.logical_or_expression()
            if not self.inputState.guessing:
                node = checknode(lx)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [QUESTIONMARK]:
                pass
                self.match(QUESTIONMARK)
                e=self.expression()
                self.match(COLON)
                cx=self.conditional_expression()
                if not self.inputState.guessing:
                    node = self.autonode([checknode(lx), checknode(e), checknode(cx)], "?:")
            elif la1 and la1 in [GREATERTHAN,SEMICOLON,RCURLY,ASSIGNEQUAL,COLON,COMMA,LITERAL___attribute__,RPAREN,RSQUARE,ELLIPSIS,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_110)
            else:
                raise ex
        
        return node
    
    def logical_or_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.logical_and_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==OR):
                    pass
                    self.match(OR)
                    x=self.logical_and_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, "||")
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_111)
            else:
                raise ex
        
        return node
    
    def logical_and_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.inclusive_or_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==AND):
                    pass
                    self.match(AND)
                    x=self.inclusive_or_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, "&&")
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_112)
            else:
                raise ex
        
        return node
    
    def inclusive_or_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.exclusive_or_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==BITWISEOR):
                    pass
                    self.match(BITWISEOR)
                    x=self.exclusive_or_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, "|")
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_113)
            else:
                raise ex
        
        return node
    
    def exclusive_or_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.and_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==BITWISEXOR):
                    pass
                    self.match(BITWISEXOR)
                    x=self.and_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, "^")
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_114)
            else:
                raise ex
        
        return node
    
    def and_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.equality_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==AMPERSAND):
                    pass
                    self.match(AMPERSAND)
                    x=self.equality_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, "&")
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_115)
            else:
                raise ex
        
        return node
    
    def equality_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.relational_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==NOTEQUAL or self.LA(1)==EQUAL):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [NOTEQUAL]:
                        pass
                        self.match(NOTEQUAL)
                        if not self.inputState.guessing:
                            leaf = "!="
                    elif la1 and la1 in [EQUAL]:
                        pass
                        self.match(EQUAL)
                        if not self.inputState.guessing:
                            leaf = "=="
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    x=self.relational_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, leaf)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_116)
            else:
                raise ex
        
        return node
    
    def relational_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.shift_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (_tokenSet_117.member(self.LA(1))) and (_tokenSet_66.member(self.LA(2))):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LESSTHAN]:
                        pass
                        self.match(LESSTHAN)
                        if not self.inputState.guessing:
                            leaf = "<"
                    elif la1 and la1 in [GREATERTHAN]:
                        pass
                        self.match(GREATERTHAN)
                        if not self.inputState.guessing:
                            leaf = ">"
                    elif la1 and la1 in [LESSTHANOREQUALTO]:
                        pass
                        self.match(LESSTHANOREQUALTO)
                        if not self.inputState.guessing:
                            leaf = "<="
                    elif la1 and la1 in [GREATERTHANOREQUALTO]:
                        pass
                        self.match(GREATERTHANOREQUALTO)
                        if not self.inputState.guessing:
                            leaf = ">="
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    x=self.shift_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, leaf)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_118)
            else:
                raise ex
        
        return node
    
    def additive_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.multiplicative_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==PLUS or self.LA(1)==MINUS):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [PLUS]:
                        pass
                        self.match(PLUS)
                        if not self.inputState.guessing:
                            leaf = "+"
                    elif la1 and la1 in [MINUS]:
                        pass
                        self.match(MINUS)
                        if not self.inputState.guessing:
                            leaf = "-"
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    x=self.multiplicative_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, leaf)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_119)
            else:
                raise ex
        
        return node
    
    def multiplicative_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.pm_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (_tokenSet_120.member(self.LA(1))):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [STAR]:
                        pass
                        self.match(STAR)
                        if not self.inputState.guessing:
                            leaf = "*"
                    elif la1 and la1 in [DIVIDE]:
                        pass
                        self.match(DIVIDE)
                        if not self.inputState.guessing:
                            leaf = "/"
                    elif la1 and la1 in [MOD]:
                        pass
                        self.match(MOD)
                        if not self.inputState.guessing:
                            leaf = "%"
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    x=self.pm_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, leaf)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_121)
            else:
                raise ex
        
        return node
    
    def pm_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            x=self.cast_expression()
            if not self.inputState.guessing:
                node = x
            while True:
                if (self.LA(1)==DOTMBR or self.LA(1)==POINTERTOMBR):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [DOTMBR]:
                        pass
                        self.match(DOTMBR)
                        if not self.inputState.guessing:
                            leaf = ".*"
                    elif la1 and la1 in [POINTERTOMBR]:
                        pass
                        self.match(POINTERTOMBR)
                        if not self.inputState.guessing:
                            leaf = "->*"
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    x=self.cast_expression()
                    if not self.inputState.guessing:
                        node = self.exprnode_acc(node, x, leaf)
                else:
                    break
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_122)
            else:
                raise ex
        
        return node
    
    def cast_expression(self):    
        node = None
        
        try:      ## for error handling
            synPredMatched410 = False
            if (self.LA(1)==LPAREN) and (_tokenSet_13.member(self.LA(2))):
                _m410 = self.mark()
                synPredMatched410 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.compound_literal()
                except antlr.RecognitionException, pe:
                    synPredMatched410 = False
                self.rewind(_m410)
                self.inputState.guessing -= 1
            if synPredMatched410:
                pass
                x=self.compound_literal()
                if not self.inputState.guessing:
                    node = x
            else:
                synPredMatched414 = False
                if (self.LA(1)==LPAREN) and (_tokenSet_123.member(self.LA(2))):
                    _m414 = self.mark()
                    synPredMatched414 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.match(LPAREN)
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LITERAL_const,LITERAL_const_cast,LITERAL_volatile]:
                            pass
                            self.type_qualifier()
                        elif la1 and la1 in [ID,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,SCOPE]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.simple_type_specifier()
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,STAR,AMPERSAND,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                            pass
                            self.ptr_operator()
                        elif la1 and la1 in [RPAREN]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.match(RPAREN)
                    except antlr.RecognitionException, pe:
                        synPredMatched414 = False
                    self.rewind(_m414)
                    self.inputState.guessing -= 1
                if synPredMatched414:
                    pass
                    self.match(LPAREN)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_const,LITERAL_const_cast,LITERAL_volatile]:
                        pass
                        tq=self.type_qualifier()
                    elif la1 and la1 in [ID,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,SCOPE]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    ts=self.simple_type_specifier()
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,STAR,AMPERSAND,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                        pass
                        po=self.ptr_operator()
                    elif la1 and la1 in [RPAREN]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(RPAREN)
                    cx=self.cast_expression()
                    if not self.inputState.guessing:
                        node = self.unfinishednode()
                elif (_tokenSet_66.member(self.LA(1))) and (_tokenSet_69.member(self.LA(2))):
                    pass
                    x=self.unary_expression()
                    if not self.inputState.guessing:
                        node = x
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
        return node
    
    def compound_literal(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(LPAREN)
            tn=self.type_name()
            self.match(RPAREN)
            self.match(LCURLY)
            i=self.initializer()
            self.match(RCURLY)
            if not self.inputState.guessing:
                node = self.autonode([tn, i])
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
        return node
    
    def unary_expression(self):    
        node = None
        
        s = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [PLUSPLUS]:
                pass
                self.match(PLUSPLUS)
                x=self.unary_expression()
                if not self.inputState.guessing:
                    node = self.autonode([x], "++."); node.set_result("++" + node.result)
            elif la1 and la1 in [MINUSMINUS]:
                pass
                self.match(MINUSMINUS)
                x=self.unary_expression()
                if not self.inputState.guessing:
                    node = self.autonode([x], "--."); node.set_result("--" + node.result)
            elif la1 and la1 in [LITERAL_sizeof]:
                pass
                self.match(LITERAL_sizeof)
                if not self.inputState.guessing:
                    node = self.autonode(None, "sizeof")
                if ((self.LA(1)==LPAREN) and (_tokenSet_13.member(self.LA(2))) and ((not (((self.LA(1)==LPAREN and (self.LA(2)==ID)))) or (self.isTypeName(self.LT(2).getText()))))):
                    pass
                    self.match(LPAREN)
                    x=self.type_name()
                    self.match(RPAREN)
                    if not self.inputState.guessing:
                        node.add_child(x)
                elif (_tokenSet_66.member(self.LA(1))) and (_tokenSet_69.member(self.LA(2))):
                    pass
                    x=self.unary_expression()
                    if not self.inputState.guessing:
                        node.add_child(x)
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            else:
                synPredMatched420 = False
                if (_tokenSet_125.member(self.LA(1))) and (_tokenSet_126.member(self.LA(2))):
                    _m420 = self.mark()
                    synPredMatched420 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.postfix_expression()
                    except antlr.RecognitionException, pe:
                        synPredMatched420 = False
                    self.rewind(_m420)
                    self.inputState.guessing -= 1
                if synPredMatched420:
                    pass
                    x=self.postfix_expression()
                    if not self.inputState.guessing:
                        node = x
                elif (_tokenSet_127.member(self.LA(1))) and (_tokenSet_66.member(self.LA(2))):
                    pass
                    op=self.unary_operator()
                    x=self.cast_expression()
                    if not self.inputState.guessing:
                        node = self.autonode([x], op); node.set_result(None)
                elif (_tokenSet_128.member(self.LA(1))) and (_tokenSet_129.member(self.LA(2))):
                    pass
                    if not self.inputState.guessing:
                        node = self.autonode()
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [SCOPE]:
                        pass
                        s = self.LT(1)
                        self.match(SCOPE)
                        if not self.inputState.guessing:
                            node.set_leaf(s)
                    elif la1 and la1 in [LITERAL_new,LITERAL_delete]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_new]:
                        pass
                        x=self.new_expression()
                        if not self.inputState.guessing:
                            node.add_child(x)
                    elif la1 and la1 in [LITERAL_delete]:
                        pass
                        x=self.delete_expression()
                        if not self.inputState.guessing:
                            node.add_child(x)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
        return node
    
    def postfix_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            synPredMatched427 = False
            if ((_tokenSet_96.member(self.LA(1))) and (_tokenSet_130.member(self.LA(2))) and ((self.LA(1) != LPAREN))):
                _m427 = self.mark()
                synPredMatched427 = True
                self.inputState.guessing += 1
                try:
                    pass
                    ts=self.simple_type_specifier()
                    self.match(LPAREN)
                    self.match(RPAREN)
                    self.match(LPAREN)
                except antlr.RecognitionException, pe:
                    synPredMatched427 = False
                self.rewind(_m427)
                self.inputState.guessing -= 1
            if synPredMatched427:
                pass
                ts=self.simple_type_specifier()
                self.match(LPAREN)
                self.match(RPAREN)
                self.match(LPAREN)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                    pass
                    el=self.expression_list()
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(RPAREN)
                if not self.inputState.guessing:
                    node = self.unfinishednode()
            else:
                synPredMatched430 = False
                if ((_tokenSet_96.member(self.LA(1))) and (_tokenSet_130.member(self.LA(2))) and ((self.LA(1) != LPAREN))):
                    _m430 = self.mark()
                    synPredMatched430 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        ts=self.simple_type_specifier()
                        self.match(LPAREN)
                    except antlr.RecognitionException, pe:
                        synPredMatched430 = False
                    self.rewind(_m430)
                    self.inputState.guessing -= 1
                if synPredMatched430:
                    pass
                    ts=self.simple_type_specifier()
                    self.match(LPAREN)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                        pass
                        el=self.expression_list()
                    elif la1 and la1 in [RPAREN]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(RPAREN)
                    if not self.inputState.guessing:
                        node = self.unfinishednode()
                elif (_tokenSet_131.member(self.LA(1))) and (_tokenSet_126.member(self.LA(2))):
                    pass
                    x=self.primary_expression()
                    if not self.inputState.guessing:
                        node = x
                    while True:
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LSQUARE]:
                            pass
                            self.match(LSQUARE)
                            x=self.expression()
                            self.match(RSQUARE)
                            if not self.inputState.guessing:
                                node = self.autonode([node, x], "[]")
                        elif la1 and la1 in [LPAREN]:
                            pass
                            self.match(LPAREN)
                            if not self.inputState.guessing:
                                node = self.autonode([node], "()")
                            la1 = self.LA(1)
                            if False:
                                pass
                            elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                                pass
                                x=self.expression_list()
                                if not self.inputState.guessing:
                                    node = self.autonode([node, x], "()")
                            elif la1 and la1 in [RPAREN]:
                                pass
                            else:
                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                
                            self.match(RPAREN)
                        elif la1 and la1 in [DOT]:
                            pass
                            self.match(DOT)
                            idxpr=self.id_expression()
                            if not self.inputState.guessing:
                                node = self.autonode([node], [".", idxpr])
                        elif la1 and la1 in [POINTERTO]:
                            pass
                            self.match(POINTERTO)
                            idxpr2=self.id_expression()
                            if not self.inputState.guessing:
                                node = self.autonode([node], ["->", idxpr2])
                        elif la1 and la1 in [PLUSPLUS]:
                            pass
                            self.match(PLUSPLUS)
                            if not self.inputState.guessing:
                                node = self.autonode([node], "++")
                        elif la1 and la1 in [MINUSMINUS]:
                            pass
                            self.match(MINUSMINUS)
                            if not self.inputState.guessing:
                                node = self.autonode([node], "--")
                        else:
                                break
                            
                elif (_tokenSet_132.member(self.LA(1))):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_dynamic_cast]:
                        pass
                        self.match(LITERAL_dynamic_cast)
                    elif la1 and la1 in [LITERAL_static_cast]:
                        pass
                        self.match(LITERAL_static_cast)
                    elif la1 and la1 in [LITERAL_reinterpret_cast]:
                        pass
                        self.match(LITERAL_reinterpret_cast)
                    elif la1 and la1 in [LITERAL_const_cast]:
                        pass
                        self.match(LITERAL_const_cast)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(LESSTHAN)
                    ts=self.type_specifier(ds)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,STAR,AMPERSAND,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                        pass
                        po=self.ptr_operator()
                    elif la1 and la1 in [GREATERTHAN]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.match(GREATERTHAN)
                    self.match(LPAREN)
                    x=self.expression()
                    self.match(RPAREN)
                    if not self.inputState.guessing:
                        node = self.unfinishednode()
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
        return node
    
    def unary_operator(self):    
        op = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [AMPERSAND]:
                pass
                self.match(AMPERSAND)
                if not self.inputState.guessing:
                    op = "&"
            elif la1 and la1 in [STAR]:
                pass
                self.match(STAR)
                if not self.inputState.guessing:
                    op = "*"
            elif la1 and la1 in [PLUS]:
                pass
                self.match(PLUS)
                if not self.inputState.guessing:
                    op = "+"
            elif la1 and la1 in [MINUS]:
                pass
                self.match(MINUS)
                if not self.inputState.guessing:
                    op = "-"
            elif la1 and la1 in [TILDE]:
                pass
                self.match(TILDE)
                if not self.inputState.guessing:
                    op = "~"
            elif la1 and la1 in [NOT]:
                pass
                self.match(NOT)
                if not self.inputState.guessing:
                    op = "~"
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_66)
            else:
                raise ex
        
        return op
    
    def new_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            pass
            self.match(LITERAL_new)
            synPredMatched447 = False
            if (self.LA(1)==LPAREN) and (_tokenSet_66.member(self.LA(2))):
                _m447 = self.mark()
                synPredMatched447 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.match(LPAREN)
                    self.expression_list()
                    self.match(RPAREN)
                except antlr.RecognitionException, pe:
                    synPredMatched447 = False
                self.rewind(_m447)
                self.inputState.guessing -= 1
            if synPredMatched447:
                pass
                self.match(LPAREN)
                el=self.expression_list()
                self.match(RPAREN)
            elif (_tokenSet_133.member(self.LA(1))) and (_tokenSet_134.member(self.LA(2))):
                pass
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_enum,ID,LITERAL_inline,LITERAL_extern,LITERAL__inline,LITERAL___inline,LITERAL_virtual,LITERAL_explicit,LITERAL_friend,LITERAL__stdcall,LITERAL___stdcall,LITERAL_typename,LITERAL_const,LITERAL_auto,LITERAL_register,LITERAL_static,LITERAL_mutable,LITERAL_const_cast,LITERAL_volatile,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,LITERAL_class,LITERAL_struct,LITERAL_union,SCOPE]:
                pass
                self.new_type_id()
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                tn=self.type_name()
                self.match(RPAREN)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LPAREN]:
                pass
                self.new_initializer()
            elif la1 and la1 in [LESSTHAN,GREATERTHAN,SEMICOLON,RCURLY,ASSIGNEQUAL,COLON,COMMA,LITERAL___attribute__,RPAREN,STAR,AMPERSAND,RSQUARE,ELLIPSIS,TIMESEQUAL,DIVIDEEQUAL,MINUSEQUAL,PLUSEQUAL,MODEQUAL,SHIFTLEFTEQUAL,SHIFTRIGHTEQUAL,BITWISEANDEQUAL,BITWISEXOREQUAL,BITWISEOREQUAL,QUESTIONMARK,OR,AND,BITWISEOR,BITWISEXOR,NOTEQUAL,EQUAL,LESSTHANOREQUALTO,GREATERTHANOREQUALTO,SHIFTLEFT,SHIFTRIGHT,PLUS,MINUS,DIVIDE,MOD,DOTMBR,POINTERTOMBR]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            if not self.inputState.guessing:
                node = self.unfinishednode()
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
        return node
    
    def delete_expression(self):    
        node = None
        
        try:      ## for error handling
            pass
            self.match(LITERAL_delete)
            if not self.inputState.guessing:
                node = self.node("delete")
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LSQUARE]:
                pass
                self.match(LSQUARE)
                self.match(RSQUARE)
                if not self.inputState.guessing:
                    node.set_leaf("[]")
            elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            cx=self.cast_expression()
            if not self.inputState.guessing:
                node.add_child(cx)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
        return node
    
    def primary_expression(self):    
        node = None
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,OPERATOR,TILDE,SCOPE]:
                pass
                x=self.id_expression()
                if not self.inputState.guessing:
                    node = self.exprnode(None, x, result = x)
            elif la1 and la1 in [StringLiteral,LITERAL_true,LITERAL_false,OCTALINT,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                pass
                x=self.constant()
                if not self.inputState.guessing:
                    node = self.exprnode(None, x, result = x)
            elif la1 and la1 in [LITERAL_this]:
                pass
                self.match(LITERAL_this)
                if not self.inputState.guessing:
                    node = self.exprnode(None, "this", result = "this")
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                x=self.expression()
                self.match(RPAREN)
                if not self.inputState.guessing:
                    node = x
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_135)
            else:
                raise ex
        
        return node
    
    def id_expression(self):    
        out = None
        
        id1 = None
        id2 = None
        try:      ## for error handling
            pass
            out=self.scope_override()
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID]:
                pass
                id1 = self.LT(1)
                self.match(ID)
                if not self.inputState.guessing:
                    out += id1.getText()
            elif la1 and la1 in [OPERATOR]:
                pass
                self.match(OPERATOR)
                o=self.optor()
                if not self.inputState.guessing:
                    out += "operator " + o
            elif la1 and la1 in [TILDE]:
                pass
                self.match(TILDE)
                if not self.inputState.guessing:
                    out += "~"
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [STAR]:
                    pass
                    self.match(STAR)
                    if not self.inputState.guessing:
                        out += "*"
                elif la1 and la1 in [ID]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                id2 = self.LT(1)
                self.match(ID)
                if not self.inputState.guessing:
                    out += id2.getText()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_135)
            else:
                raise ex
        
        return out
    
    def constant(self):    
        out = None
        
        oi = None
        di = None
        hi = None
        cl = None
        sl = None
        f1 = None
        f2 = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [OCTALINT]:
                pass
                if not self.inputState.guessing:
                    out = ""
                oi = self.LT(1)
                self.match(OCTALINT)
                if not self.inputState.guessing:
                    out = oi.getText()
            elif la1 and la1 in [DECIMALINT]:
                pass
                di = self.LT(1)
                self.match(DECIMALINT)
                if not self.inputState.guessing:
                    out = di.getText()
            elif la1 and la1 in [HEXADECIMALINT]:
                pass
                hi = self.LT(1)
                self.match(HEXADECIMALINT)
                if not self.inputState.guessing:
                    out = hi.getText()
            elif la1 and la1 in [CharLiteral]:
                pass
                cl = self.LT(1)
                self.match(CharLiteral)
                if not self.inputState.guessing:
                    out = cl.getText()
            elif la1 and la1 in [StringLiteral]:
                pass
                _cnt481= 0
                while True:
                    if (self.LA(1)==StringLiteral):
                        pass
                        sl = self.LT(1)
                        self.match(StringLiteral)
                        if not self.inputState.guessing:
                            out += sl.getText()
                    else:
                        break
                    
                    _cnt481 += 1
                if _cnt481 < 1:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            elif la1 and la1 in [FLOATONE]:
                pass
                f1 = self.LT(1)
                self.match(FLOATONE)
                if not self.inputState.guessing:
                    out = f1.getText()
            elif la1 and la1 in [FLOATTWO]:
                pass
                f2 = self.LT(1)
                self.match(FLOATTWO)
                if not self.inputState.guessing:
                    out = f2.getText()
            elif la1 and la1 in [LITERAL_true]:
                pass
                self.match(LITERAL_true)
                if not self.inputState.guessing:
                    out = "true"
            elif la1 and la1 in [LITERAL_false]:
                pass
                self.match(LITERAL_false)
                if not self.inputState.guessing:
                    out = "false"
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_135)
            else:
                raise ex
        
        return out
    
    def new_type_id(self):    
        
        try:      ## for error handling
            pass
            ds=self.declaration_specifiers()
            if (_tokenSet_136.member(self.LA(1))) and (_tokenSet_137.member(self.LA(2))):
                pass
                self.new_declarator()
            elif (_tokenSet_138.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                pass
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_138)
            else:
                raise ex
        
    
    def new_initializer(self):    
        
        try:      ## for error handling
            pass
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,StringLiteral,LPAREN,LITERAL_const_cast,LITERAL_char,LITERAL_wchar_t,LITERAL_bool,LITERAL_short,LITERAL_int,44,45,46,LITERAL_long,LITERAL_signed,LITERAL_unsigned,LITERAL_float,LITERAL_double,LITERAL_void,LITERAL__declspec,LITERAL___declspec,OPERATOR,LITERAL_this,LITERAL_true,LITERAL_false,OCTALINT,STAR,AMPERSAND,TILDE,PLUS,MINUS,PLUSPLUS,MINUSMINUS,LITERAL_sizeof,SCOPE,LITERAL_dynamic_cast,LITERAL_static_cast,LITERAL_reinterpret_cast,NOT,LITERAL_new,LITERAL_delete,DECIMALINT,HEXADECIMALINT,CharLiteral,FLOATONE,FLOATTWO]:
                pass
                el=self.expression_list()
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_124)
            else:
                raise ex
        
    
    def new_declarator(self):    
        
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [ID,LITERAL__stdcall,LITERAL___stdcall,STAR,AMPERSAND,SCOPE,LITERAL__cdecl,LITERAL___cdecl,LITERAL__near,LITERAL___near,LITERAL__far,LITERAL___far,LITERAL___interrupt,LITERAL_pascal,LITERAL__pascal,LITERAL___pascal]:
                pass
                po=self.ptr_operator()
                if (_tokenSet_136.member(self.LA(1))) and (_tokenSet_137.member(self.LA(2))):
                    pass
                    self.new_declarator()
                elif (_tokenSet_138.member(self.LA(1))) and (_tokenSet_37.member(self.LA(2))):
                    pass
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            elif la1 and la1 in [LSQUARE]:
                pass
                self.direct_new_declarator()
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_138)
            else:
                raise ex
        
    
    def direct_new_declarator(self):    
        
        try:      ## for error handling
            pass
            _cnt473= 0
            while True:
                if (self.LA(1)==LSQUARE):
                    pass
                    self.match(LSQUARE)
                    x=self.expression()
                    self.match(RSQUARE)
                else:
                    break
                
                _cnt473 += 1
            if _cnt473 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_138)
            else:
                raise ex
        
    
    def ptr_to_member(self):    
        ptm = None
        
        try:      ## for error handling
            pass
            s=self.scope_override()
            if not self.inputState.guessing:
                ptm = s
            self.match(STAR)
            if not self.inputState.guessing:
                ptm += "*"
            if not self.inputState.guessing:
                self.is_pointer = True
            cvs=self.cv_qualifier_seq()
            if not self.inputState.guessing:
                ptm += cvs
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        return ptm
    
    def optor_simple_tokclass(self):    
        out = None
        
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [PLUS]:
                pass
                self.match(PLUS)
            elif la1 and la1 in [MINUS]:
                pass
                self.match(MINUS)
            elif la1 and la1 in [STAR]:
                pass
                self.match(STAR)
            elif la1 and la1 in [DIVIDE]:
                pass
                self.match(DIVIDE)
            elif la1 and la1 in [MOD]:
                pass
                self.match(MOD)
            elif la1 and la1 in [BITWISEXOR]:
                pass
                self.match(BITWISEXOR)
            elif la1 and la1 in [AMPERSAND]:
                pass
                self.match(AMPERSAND)
            elif la1 and la1 in [BITWISEOR]:
                pass
                self.match(BITWISEOR)
            elif la1 and la1 in [TILDE]:
                pass
                self.match(TILDE)
            elif la1 and la1 in [NOT]:
                pass
                self.match(NOT)
            elif la1 and la1 in [SHIFTLEFT]:
                pass
                self.match(SHIFTLEFT)
            elif la1 and la1 in [SHIFTRIGHT]:
                pass
                self.match(SHIFTRIGHT)
            elif la1 and la1 in [ASSIGNEQUAL]:
                pass
                self.match(ASSIGNEQUAL)
            elif la1 and la1 in [TIMESEQUAL]:
                pass
                self.match(TIMESEQUAL)
            elif la1 and la1 in [DIVIDEEQUAL]:
                pass
                self.match(DIVIDEEQUAL)
            elif la1 and la1 in [MODEQUAL]:
                pass
                self.match(MODEQUAL)
            elif la1 and la1 in [PLUSEQUAL]:
                pass
                self.match(PLUSEQUAL)
            elif la1 and la1 in [MINUSEQUAL]:
                pass
                self.match(MINUSEQUAL)
            elif la1 and la1 in [SHIFTLEFTEQUAL]:
                pass
                self.match(SHIFTLEFTEQUAL)
            elif la1 and la1 in [SHIFTRIGHTEQUAL]:
                pass
                self.match(SHIFTRIGHTEQUAL)
            elif la1 and la1 in [BITWISEANDEQUAL]:
                pass
                self.match(BITWISEANDEQUAL)
            elif la1 and la1 in [BITWISEXOREQUAL]:
                pass
                self.match(BITWISEXOREQUAL)
            elif la1 and la1 in [BITWISEOREQUAL]:
                pass
                self.match(BITWISEOREQUAL)
            elif la1 and la1 in [EQUAL]:
                pass
                self.match(EQUAL)
            elif la1 and la1 in [NOTEQUAL]:
                pass
                self.match(NOTEQUAL)
            elif la1 and la1 in [LESSTHAN]:
                pass
                self.match(LESSTHAN)
            elif la1 and la1 in [GREATERTHAN]:
                pass
                self.match(GREATERTHAN)
            elif la1 and la1 in [LESSTHANOREQUALTO]:
                pass
                self.match(LESSTHANOREQUALTO)
            elif la1 and la1 in [GREATERTHANOREQUALTO]:
                pass
                self.match(GREATERTHANOREQUALTO)
            elif la1 and la1 in [OR]:
                pass
                self.match(OR)
            elif la1 and la1 in [AND]:
                pass
                self.match(AND)
            elif la1 and la1 in [PLUSPLUS]:
                pass
                self.match(PLUSPLUS)
            elif la1 and la1 in [MINUSMINUS]:
                pass
                self.match(MINUSMINUS)
            elif la1 and la1 in [COMMA]:
                pass
                self.match(COMMA)
            elif la1 and la1 in [POINTERTO]:
                pass
                self.match(POINTERTO)
            elif la1 and la1 in [POINTERTOMBR]:
                pass
                self.match(POINTERTOMBR)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_60)
            else:
                raise ex
        
        return out
    

_tokenNames = [
    "<0>", 
    "EOF", 
    "<2>", 
    "NULL_TREE_LOOKAHEAD", 
    "\"template\"", 
    "LESSTHAN", 
    "GREATERTHAN", 
    "\"typedef\"", 
    "\"enum\"", 
    "ID", 
    "LCURLY", 
    "SEMICOLON", 
    "\"inline\"", 
    "\"namespace\"", 
    "RCURLY", 
    "ASSIGNEQUAL", 
    "COLON", 
    "\"extern\"", 
    "StringLiteral", 
    "COMMA", 
    "\"_inline\"", 
    "\"__inline\"", 
    "\"virtual\"", 
    "\"explicit\"", 
    "\"friend\"", 
    "\"_stdcall\"", 
    "\"__stdcall\"", 
    "\"typename\"", 
    "\"__attribute__\"", 
    "LPAREN", 
    "RPAREN", 
    "\"__mode__\"", 
    "\"const\"", 
    "\"auto\"", 
    "\"register\"", 
    "\"static\"", 
    "\"mutable\"", 
    "\"const_cast\"", 
    "\"volatile\"", 
    "\"char\"", 
    "\"wchar_t\"", 
    "\"bool\"", 
    "\"short\"", 
    "\"int\"", 
    "\"_int64\"", 
    "\"__int64\"", 
    "\"__w64\"", 
    "\"long\"", 
    "\"signed\"", 
    "\"unsigned\"", 
    "\"float\"", 
    "\"double\"", 
    "\"void\"", 
    "\"_declspec\"", 
    "\"__declspec\"", 
    "\"class\"", 
    "\"struct\"", 
    "\"union\"", 
    "\"operator\"", 
    "\"this\"", 
    "\"true\"", 
    "\"false\"", 
    "DOT", 
    "EQUALS", 
    "\"public\"", 
    "\"protected\"", 
    "\"private\"", 
    "OCTALINT", 
    "STAR", 
    "AMPERSAND", 
    "LSQUARE", 
    "RSQUARE", 
    "TILDE", 
    "ELLIPSIS", 
    "\"throw\"", 
    "\"case\"", 
    "\"default\"", 
    "\"if\"", 
    "\"else\"", 
    "\"switch\"", 
    "\"while\"", 
    "\"do\"", 
    "\"for\"", 
    "\"goto\"", 
    "\"continue\"", 
    "\"break\"", 
    "\"return\"", 
    "\"try\"", 
    "\"catch\"", 
    "\"using\"", 
    "\"_asm\"", 
    "\"__asm\"", 
    "\"__asm__\"", 
    "\"asm\"", 
    "TIMESEQUAL", 
    "DIVIDEEQUAL", 
    "MINUSEQUAL", 
    "PLUSEQUAL", 
    "MODEQUAL", 
    "SHIFTLEFTEQUAL", 
    "SHIFTRIGHTEQUAL", 
    "BITWISEANDEQUAL", 
    "BITWISEXOREQUAL", 
    "BITWISEOREQUAL", 
    "QUESTIONMARK", 
    "OR", 
    "AND", 
    "BITWISEOR", 
    "BITWISEXOR", 
    "NOTEQUAL", 
    "EQUAL", 
    "LESSTHANOREQUALTO", 
    "GREATERTHANOREQUALTO", 
    "SHIFTLEFT", 
    "SHIFTRIGHT", 
    "PLUS", 
    "MINUS", 
    "DIVIDE", 
    "MOD", 
    "DOTMBR", 
    "POINTERTOMBR", 
    "PLUSPLUS", 
    "MINUSMINUS", 
    "\"sizeof\"", 
    "SCOPE", 
    "POINTERTO", 
    "\"dynamic_cast\"", 
    "\"static_cast\"", 
    "\"reinterpret_cast\"", 
    "NOT", 
    "\"new\"", 
    "\"_cdecl\"", 
    "\"__cdecl\"", 
    "\"_near\"", 
    "\"__near\"", 
    "\"_far\"", 
    "\"__far\"", 
    "\"__interrupt\"", 
    "\"pascal\"", 
    "\"_pascal\"", 
    "\"__pascal\"", 
    "\"delete\"", 
    "DECIMALINT", 
    "HEXADECIMALINT", 
    "CharLiteral", 
    "FLOATONE", 
    "FLOATTWO", 
    "Whitespace", 
    "Comment", 
    "CPPComment", 
    "a line directive", 
    "LineDirective", 
    "Space", 
    "Pragma", 
    "Error", 
    "EndOfLine", 
    "Escape", 
    "Digit", 
    "Decimal", 
    "LongSuffix", 
    "UnsignedSuffix", 
    "FloatSuffix", 
    "Exponent", 
    "Vocabulary", 
    "Number"
]
    

### generate bit set
def mk_tokenSet_0(): 
    ### var1
    data = [ 4611686014936824720L, 1152921504640401712L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_0 = antlr.BitSet(mk_tokenSet_0())

### generate bit set
def mk_tokenSet_1(): 
    ### var1
    data = [ 2L, 0L, 0L]
    return data
_tokenSet_1 = antlr.BitSet(mk_tokenSet_1())

### generate bit set
def mk_tokenSet_2(): 
    ### var1
    data = [ 288230372124267392L, 1152921504640401408L, 0L, 0L]
    return data
_tokenSet_2 = antlr.BitSet(mk_tokenSet_2())

### generate bit set
def mk_tokenSet_3(): 
    ### var1
    data = [ 4611686015071829920L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_3 = antlr.BitSet(mk_tokenSet_3())

### generate bit set
def mk_tokenSet_4(): 
    ### var1
    data = [ 7344656L, 1152921504606847232L, 0L, 0L]
    return data
_tokenSet_4 = antlr.BitSet(mk_tokenSet_4())

### generate bit set
def mk_tokenSet_5(): 
    ### var1
    data = [ 7344672L, 1152921504606847232L, 0L, 0L]
    return data
_tokenSet_5 = antlr.BitSet(mk_tokenSet_5())

### generate bit set
def mk_tokenSet_6(): 
    ### var1
    data = [ 11538944L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_6 = antlr.BitSet(mk_tokenSet_6())

### generate bit set
def mk_tokenSet_7(): 
    ### var1
    data = [ 548409888L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_7 = antlr.BitSet(mk_tokenSet_7())

### generate bit set
def mk_tokenSet_8(): 
    ### var1
    data = [ 288230376151716352L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_8 = antlr.BitSet(mk_tokenSet_8())

### generate bit set
def mk_tokenSet_9(): 
    ### var1
    data = [ 576460748275979168L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_9 = antlr.BitSet(mk_tokenSet_9())

### generate bit set
def mk_tokenSet_10(): 
    ### var1
    data = [ 4611686014936814464L, 1152921504606847024L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_10 = antlr.BitSet(mk_tokenSet_10())

### generate bit set
def mk_tokenSet_11(): 
    ### var1
    data = [ 4611686014803154912L, 3999195368519631216L, 16382L, 0L, 0L, 0L]
    return data
_tokenSet_11 = antlr.BitSet(mk_tokenSet_11())

### generate bit set
def mk_tokenSet_12(): 
    ### var1
    data = [ 4611686014936841106L, 1152921504640401712L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_12 = antlr.BitSet(mk_tokenSet_12())

### generate bit set
def mk_tokenSet_13(): 
    ### var1
    data = [ 288230372124267392L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_13 = antlr.BitSet(mk_tokenSet_13())

### generate bit set
def mk_tokenSet_14(): 
    ### var1
    data = [ 4611686015071559584L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_14 = antlr.BitSet(mk_tokenSet_14())

### generate bit set
def mk_tokenSet_15(): 
    ### var1
    data = [ 4611686014937104274L, -2443202796791530177L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_15 = antlr.BitSet(mk_tokenSet_15())

### generate bit set
def mk_tokenSet_16(): 
    ### var1
    data = [ 4611686014936814464L, 1152921504640401712L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_16 = antlr.BitSet(mk_tokenSet_16())

### generate bit set
def mk_tokenSet_17(): 
    ### var1
    data = [ 4323455644256029280L, 1297036691608962032L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_17 = antlr.BitSet(mk_tokenSet_17())

### generate bit set
def mk_tokenSet_18(): 
    ### var1
    data = [ 2048L, 0L, 0L]
    return data
_tokenSet_18 = antlr.BitSet(mk_tokenSet_18())

### generate bit set
def mk_tokenSet_19(): 
    ### var1
    data = [ 3072L, 0L, 0L]
    return data
_tokenSet_19 = antlr.BitSet(mk_tokenSet_19())

### generate bit set
def mk_tokenSet_20(): 
    ### var1
    data = [ 4611686014936841106L, 1152921504640401719L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_20 = antlr.BitSet(mk_tokenSet_20())

### generate bit set
def mk_tokenSet_21(): 
    ### var1
    data = [ 512L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_21 = antlr.BitSet(mk_tokenSet_21())

### generate bit set
def mk_tokenSet_22(): 
    ### var1
    data = [ 4323455642275676672L, 272L, 0L, 0L]
    return data
_tokenSet_22 = antlr.BitSet(mk_tokenSet_22())

### generate bit set
def mk_tokenSet_23(): 
    ### var1
    data = [ 100663808L, 1152921504606847024L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_23 = antlr.BitSet(mk_tokenSet_23())

### generate bit set
def mk_tokenSet_24(): 
    ### var1
    data = [ 4323456059525038624L, 1152921504606847024L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_24 = antlr.BitSet(mk_tokenSet_24())

### generate bit set
def mk_tokenSet_25(): 
    ### var1
    data = [ 4323455642812547584L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_25 = antlr.BitSet(mk_tokenSet_25())

### generate bit set
def mk_tokenSet_26(): 
    ### var1
    data = [ 4323455642813104736L, 3999195368519631216L, 8198L, 0L, 0L, 0L]
    return data
_tokenSet_26 = antlr.BitSet(mk_tokenSet_26())

### generate bit set
def mk_tokenSet_27(): 
    ### var1
    data = [ 288230372124270464L, 1152921504640401408L, 0L, 0L]
    return data
_tokenSet_27 = antlr.BitSet(mk_tokenSet_27())

### generate bit set
def mk_tokenSet_28(): 
    ### var1
    data = [ 4611686014802597792L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_28 = antlr.BitSet(mk_tokenSet_28())

### generate bit set
def mk_tokenSet_29(): 
    ### var1
    data = [ 288230372124268416L, 1152921504640401408L, 0L, 0L]
    return data
_tokenSet_29 = antlr.BitSet(mk_tokenSet_29())

### generate bit set
def mk_tokenSet_30(): 
    ### var1
    data = [ 4611686015206064032L, -2443202796791546568L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_30 = antlr.BitSet(mk_tokenSet_30())

### generate bit set
def mk_tokenSet_31(): 
    ### var1
    data = [ 4611686014937096064L, -2443202796791546568L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_31 = antlr.BitSet(mk_tokenSet_31())

### generate bit set
def mk_tokenSet_32(): 
    ### var1
    data = [ 4323455642913210880L, 1152921504606847024L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_32 = antlr.BitSet(mk_tokenSet_32())

### generate bit set
def mk_tokenSet_33(): 
    ### var1
    data = [ 4323456059525595744L, 3999195368519631216L, 16382L, 0L, 0L, 0L]
    return data
_tokenSet_33 = antlr.BitSet(mk_tokenSet_33())

### generate bit set
def mk_tokenSet_34(): 
    ### var1
    data = [ 4611686014936842128L, 1152921504640401712L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_34 = antlr.BitSet(mk_tokenSet_34())

### generate bit set
def mk_tokenSet_35(): 
    ### var1
    data = [ 4611686014937076608L, -2443202797848493768L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_35 = antlr.BitSet(mk_tokenSet_35())

### generate bit set
def mk_tokenSet_36(): 
    ### var1
    data = [ 4323455644256030304L, 1297036691608962032L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_36 = antlr.BitSet(mk_tokenSet_36())

### generate bit set
def mk_tokenSet_37(): 
    ### var1
    data = [ 9223372034707292146L, -16777217L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_37 = antlr.BitSet(mk_tokenSet_37())

### generate bit set
def mk_tokenSet_38(): 
    ### var1
    data = [ 7344640L, 1152921504606847232L, 0L, 0L]
    return data
_tokenSet_38 = antlr.BitSet(mk_tokenSet_38())

### generate bit set
def mk_tokenSet_39(): 
    ### var1
    data = [ 576460748275979136L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_39 = antlr.BitSet(mk_tokenSet_39())

### generate bit set
def mk_tokenSet_40(): 
    ### var1
    data = [ 4323455642275676672L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_40 = antlr.BitSet(mk_tokenSet_40())

### generate bit set
def mk_tokenSet_41(): 
    ### var1
    data = [ 4323455642813106784L, 3999195368519631216L, 8198L, 0L, 0L, 0L]
    return data
_tokenSet_41 = antlr.BitSet(mk_tokenSet_41())

### generate bit set
def mk_tokenSet_42(): 
    ### var1
    data = [ 4611686014802665376L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_42 = antlr.BitSet(mk_tokenSet_42())

### generate bit set
def mk_tokenSet_43(): 
    ### var1
    data = [ 4611686014936832912L, 1152921504640401719L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_43 = antlr.BitSet(mk_tokenSet_43())

### generate bit set
def mk_tokenSet_44(): 
    ### var1
    data = [ 68608L, 0L, 0L]
    return data
_tokenSet_44 = antlr.BitSet(mk_tokenSet_44())

### generate bit set
def mk_tokenSet_45(): 
    ### var1
    data = [ 4611686014937104274L, -2443202796774752961L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_45 = antlr.BitSet(mk_tokenSet_45())

### generate bit set
def mk_tokenSet_46(): 
    ### var1
    data = [ 4260352L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_46 = antlr.BitSet(mk_tokenSet_46())

### generate bit set
def mk_tokenSet_47(): 
    ### var1
    data = [ 4323455642913212928L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_47 = antlr.BitSet(mk_tokenSet_47())

### generate bit set
def mk_tokenSet_48(): 
    ### var1
    data = [ 288230371990049664L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_48 = antlr.BitSet(mk_tokenSet_48())

### generate bit set
def mk_tokenSet_49(): 
    ### var1
    data = [ 4611686016279633888L, 1297036691642517488L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_49 = antlr.BitSet(mk_tokenSet_49())

### generate bit set
def mk_tokenSet_50(): 
    ### var1
    data = [ 416611827712L, 0L, 0L]
    return data
_tokenSet_50 = antlr.BitSet(mk_tokenSet_50())

### generate bit set
def mk_tokenSet_51(): 
    ### var1
    data = [ 4359484027514913280L, -2443202797848493640L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_51 = antlr.BitSet(mk_tokenSet_51())

### generate bit set
def mk_tokenSet_52(): 
    ### var1
    data = [ 4323455644256029280L, 4035225265050223600L, 16382L, 0L, 0L, 0L]
    return data
_tokenSet_52 = antlr.BitSet(mk_tokenSet_52())

### generate bit set
def mk_tokenSet_53(): 
    ### var1
    data = [ 1073741824L, 0L, 0L]
    return data
_tokenSet_53 = antlr.BitSet(mk_tokenSet_53())

### generate bit set
def mk_tokenSet_54(): 
    ### var1
    data = [ 4611686014936816528L, 1152921504640401719L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_54 = antlr.BitSet(mk_tokenSet_54())

### generate bit set
def mk_tokenSet_55(): 
    ### var1
    data = [ 64L, 0L, 0L]
    return data
_tokenSet_55 = antlr.BitSet(mk_tokenSet_55())

### generate bit set
def mk_tokenSet_56(): 
    ### var1
    data = [ 1024L, 0L, 0L]
    return data
_tokenSet_56 = antlr.BitSet(mk_tokenSet_56())

### generate bit set
def mk_tokenSet_57(): 
    ### var1
    data = [ 16384L, 0L, 0L]
    return data
_tokenSet_57 = antlr.BitSet(mk_tokenSet_57())

### generate bit set
def mk_tokenSet_58(): 
    ### var1
    data = [ 540672L, 0L, 0L]
    return data
_tokenSet_58 = antlr.BitSet(mk_tokenSet_58())

### generate bit set
def mk_tokenSet_59(): 
    ### var1
    data = [ 641024L, 128L, 0L, 0L]
    return data
_tokenSet_59 = antlr.BitSet(mk_tokenSet_59())

### generate bit set
def mk_tokenSet_60(): 
    ### var1
    data = [ 8935141662683418208L, 4035225265050223600L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_60 = antlr.BitSet(mk_tokenSet_60())

### generate bit set
def mk_tokenSet_61(): 
    ### var1
    data = [ 268961792L, 0L, 0L]
    return data
_tokenSet_61 = antlr.BitSet(mk_tokenSet_61())

### generate bit set
def mk_tokenSet_62(): 
    ### var1
    data = [ 4323456059525038624L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_62 = antlr.BitSet(mk_tokenSet_62())

### generate bit set
def mk_tokenSet_63(): 
    ### var1
    data = [ 4323455642812547584L, 1152921504606847232L, 0L, 0L]
    return data
_tokenSet_63 = antlr.BitSet(mk_tokenSet_63())

### generate bit set
def mk_tokenSet_64(): 
    ### var1
    data = [ 4323455644255947360L, 3999195368519631728L, 16382L, 0L, 0L, 0L]
    return data
_tokenSet_64 = antlr.BitSet(mk_tokenSet_64())

### generate bit set
def mk_tokenSet_65(): 
    ### var1
    data = [ 1879607360L, 512L, 0L, 0L]
    return data
_tokenSet_65 = antlr.BitSet(mk_tokenSet_65())

### generate bit set
def mk_tokenSet_66(): 
    ### var1
    data = [ 4359484027514913280L, -2443202797848493768L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_66 = antlr.BitSet(mk_tokenSet_66())

### generate bit set
def mk_tokenSet_67(): 
    ### var1
    data = [ 9223372033633475552L, -1073741448L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_67 = antlr.BitSet(mk_tokenSet_67())

### generate bit set
def mk_tokenSet_68(): 
    ### var1
    data = [ 268978176L, 0L, 0L]
    return data
_tokenSet_68 = antlr.BitSet(mk_tokenSet_68())

### generate bit set
def mk_tokenSet_69(): 
    ### var1
    data = [ 9223372034707282912L, -1073740808L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_69 = antlr.BitSet(mk_tokenSet_69())

### generate bit set
def mk_tokenSet_70(): 
    ### var1
    data = [ 1342785600L, 640L, 0L, 0L]
    return data
_tokenSet_70 = antlr.BitSet(mk_tokenSet_70())

### generate bit set
def mk_tokenSet_71(): 
    ### var1
    data = [ 8971170045942302208L, -2443202797848493768L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_71 = antlr.BitSet(mk_tokenSet_71())

### generate bit set
def mk_tokenSet_72(): 
    ### var1
    data = [ 525312L, 0L, 0L]
    return data
_tokenSet_72 = antlr.BitSet(mk_tokenSet_72())

### generate bit set
def mk_tokenSet_73(): 
    ### var1
    data = [ 4359484027514978816L, -2443202797848493768L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_73 = antlr.BitSet(mk_tokenSet_73())

### generate bit set
def mk_tokenSet_74(): 
    ### var1
    data = [ 4323455642913210880L, 1152921504606847280L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_74 = antlr.BitSet(mk_tokenSet_74())

### generate bit set
def mk_tokenSet_75(): 
    ### var1
    data = [ 4323456059525597792L, 3999195368519631216L, 16382L, 0L, 0L, 0L]
    return data
_tokenSet_75 = antlr.BitSet(mk_tokenSet_75())

### generate bit set
def mk_tokenSet_76(): 
    ### var1
    data = [ 526336L, 0L, 0L]
    return data
_tokenSet_76 = antlr.BitSet(mk_tokenSet_76())

### generate bit set
def mk_tokenSet_77(): 
    ### var1
    data = [ 4611686016279633888L, 1297036691642516464L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_77 = antlr.BitSet(mk_tokenSet_77())

### generate bit set
def mk_tokenSet_78(): 
    ### var1
    data = [ 4323455644256029280L, 1297036691608963056L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_78 = antlr.BitSet(mk_tokenSet_78())

### generate bit set
def mk_tokenSet_79(): 
    ### var1
    data = [ 288230372124303232L, 1152921504640402432L, 0L, 0L]
    return data
_tokenSet_79 = antlr.BitSet(mk_tokenSet_79())

### generate bit set
def mk_tokenSet_80(): 
    ### var1
    data = [ 66560L, 0L, 0L]
    return data
_tokenSet_80 = antlr.BitSet(mk_tokenSet_80())

### generate bit set
def mk_tokenSet_81(): 
    ### var1
    data = [ 536870912L, 0L, 0L]
    return data
_tokenSet_81 = antlr.BitSet(mk_tokenSet_81())

### generate bit set
def mk_tokenSet_82(): 
    ### var1
    data = [ 512L, 1152921504606847232L, 0L, 0L]
    return data
_tokenSet_82 = antlr.BitSet(mk_tokenSet_82())

### generate bit set
def mk_tokenSet_83(): 
    ### var1
    data = [ 1073741824L, 512L, 0L, 0L]
    return data
_tokenSet_83 = antlr.BitSet(mk_tokenSet_83())

### generate bit set
def mk_tokenSet_84(): 
    ### var1
    data = [ 4611686015876896736L, 1152921504606847856L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_84 = antlr.BitSet(mk_tokenSet_84())

### generate bit set
def mk_tokenSet_85(): 
    ### var1
    data = [ 4323456060599337568L, 3999195368519631728L, 16382L, 0L, 0L, 0L]
    return data
_tokenSet_85 = antlr.BitSet(mk_tokenSet_85())

### generate bit set
def mk_tokenSet_86(): 
    ### var1
    data = [ 1711833664L, 1152921504606847600L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_86 = antlr.BitSet(mk_tokenSet_86())

### generate bit set
def mk_tokenSet_87(): 
    ### var1
    data = [ 4611686016279896032L, -2305843010253879304L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_87 = antlr.BitSet(mk_tokenSet_87())

### generate bit set
def mk_tokenSet_88(): 
    ### var1
    data = [ 1074266176L, 512L, 0L, 0L]
    return data
_tokenSet_88 = antlr.BitSet(mk_tokenSet_88())

### generate bit set
def mk_tokenSet_89(): 
    ### var1
    data = [ 1074298944L, 512L, 0L, 0L]
    return data
_tokenSet_89 = antlr.BitSet(mk_tokenSet_89())

### generate bit set
def mk_tokenSet_90(): 
    ### var1
    data = [ 1074266176L, 0L, 0L]
    return data
_tokenSet_90 = antlr.BitSet(mk_tokenSet_90())

### generate bit set
def mk_tokenSet_91(): 
    ### var1
    data = [ 1611169856L, 576L, 0L, 0L]
    return data
_tokenSet_91 = antlr.BitSet(mk_tokenSet_91())

### generate bit set
def mk_tokenSet_92(): 
    ### var1
    data = [ 524864L, 0L, 0L]
    return data
_tokenSet_92 = antlr.BitSet(mk_tokenSet_92())

### generate bit set
def mk_tokenSet_93(): 
    ### var1
    data = [ 4611686014936814464L, 1152921504606847792L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_93 = antlr.BitSet(mk_tokenSet_93())

### generate bit set
def mk_tokenSet_94(): 
    ### var1
    data = [ 524352L, 0L, 0L]
    return data
_tokenSet_94 = antlr.BitSet(mk_tokenSet_94())

### generate bit set
def mk_tokenSet_95(): 
    ### var1
    data = [ 638059104L, 1152921504606847088L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_95 = antlr.BitSet(mk_tokenSet_95())

### generate bit set
def mk_tokenSet_96(): 
    ### var1
    data = [ 36028247263150592L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_96 = antlr.BitSet(mk_tokenSet_96())

### generate bit set
def mk_tokenSet_97(): 
    ### var1
    data = [ 36028247901209184L, 1152921504606847088L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_97 = antlr.BitSet(mk_tokenSet_97())

### generate bit set
def mk_tokenSet_98(): 
    ### var1
    data = [ 4611686014803122144L, 1152921504606847344L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_98 = antlr.BitSet(mk_tokenSet_98())

### generate bit set
def mk_tokenSet_99(): 
    ### var1
    data = [ 9223372033365021664L, -1100585369224L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_99 = antlr.BitSet(mk_tokenSet_99())

### generate bit set
def mk_tokenSet_100(): 
    ### var1
    data = [ 1342818400L, 562948879680160L, 0L, 0L]
    return data
_tokenSet_100 = antlr.BitSet(mk_tokenSet_100())

### generate bit set
def mk_tokenSet_101(): 
    ### var1
    data = [ 4611686014937079680L, -2443202796791546568L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_101 = antlr.BitSet(mk_tokenSet_101())

### generate bit set
def mk_tokenSet_102(): 
    ### var1
    data = [ 9223372033365023712L, -1073741448L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_102 = antlr.BitSet(mk_tokenSet_102())

### generate bit set
def mk_tokenSet_103(): 
    ### var1
    data = [ 4611686014937096064L, -2443202796791530184L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_103 = antlr.BitSet(mk_tokenSet_103())

### generate bit set
def mk_tokenSet_104(): 
    ### var1
    data = [ 1073809408L, 128L, 0L, 0L]
    return data
_tokenSet_104 = antlr.BitSet(mk_tokenSet_104())

### generate bit set
def mk_tokenSet_105(): 
    ### var1
    data = [ 9223372033633550322L, -641L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_105 = antlr.BitSet(mk_tokenSet_105())

### generate bit set
def mk_tokenSet_106(): 
    ### var1
    data = [ 4611686014937096064L, -2443202796774752968L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_106 = antlr.BitSet(mk_tokenSet_106())

### generate bit set
def mk_tokenSet_107(): 
    ### var1
    data = [ -16400L, -1L, 137438953471L, 0L, 0L, 0L]
    return data
_tokenSet_107 = antlr.BitSet(mk_tokenSet_107())

### generate bit set
def mk_tokenSet_108(): 
    ### var1
    data = [ 65536L, 0L, 0L]
    return data
_tokenSet_108 = antlr.BitSet(mk_tokenSet_108())

### generate bit set
def mk_tokenSet_109(): 
    ### var1
    data = [ 1073807360L, 0L, 0L]
    return data
_tokenSet_109 = antlr.BitSet(mk_tokenSet_109())

### generate bit set
def mk_tokenSet_110(): 
    ### var1
    data = [ 1342818368L, 1098437886592L, 0L, 0L]
    return data
_tokenSet_110 = antlr.BitSet(mk_tokenSet_110())

### generate bit set
def mk_tokenSet_111(): 
    ### var1
    data = [ 1342818368L, 2197949514368L, 0L, 0L]
    return data
_tokenSet_111 = antlr.BitSet(mk_tokenSet_111())

### generate bit set
def mk_tokenSet_112(): 
    ### var1
    data = [ 1342818368L, 4396972769920L, 0L, 0L]
    return data
_tokenSet_112 = antlr.BitSet(mk_tokenSet_112())

### generate bit set
def mk_tokenSet_113(): 
    ### var1
    data = [ 1342818368L, 8795019281024L, 0L, 0L]
    return data
_tokenSet_113 = antlr.BitSet(mk_tokenSet_113())

### generate bit set
def mk_tokenSet_114(): 
    ### var1
    data = [ 1342818368L, 17591112303232L, 0L, 0L]
    return data
_tokenSet_114 = antlr.BitSet(mk_tokenSet_114())

### generate bit set
def mk_tokenSet_115(): 
    ### var1
    data = [ 1342818368L, 35183298347648L, 0L, 0L]
    return data
_tokenSet_115 = antlr.BitSet(mk_tokenSet_115())

### generate bit set
def mk_tokenSet_116(): 
    ### var1
    data = [ 1342818368L, 35183298347680L, 0L, 0L]
    return data
_tokenSet_116 = antlr.BitSet(mk_tokenSet_116())

### generate bit set
def mk_tokenSet_117(): 
    ### var1
    data = [ 96L, 422212465065984L, 0L, 0L]
    return data
_tokenSet_117 = antlr.BitSet(mk_tokenSet_117())

### generate bit set
def mk_tokenSet_118(): 
    ### var1
    data = [ 1342818368L, 140736414614176L, 0L, 0L]
    return data
_tokenSet_118 = antlr.BitSet(mk_tokenSet_118())

### generate bit set
def mk_tokenSet_119(): 
    ### var1
    data = [ 1342818400L, 2251798739944096L, 0L, 0L]
    return data
_tokenSet_119 = antlr.BitSet(mk_tokenSet_119())

### generate bit set
def mk_tokenSet_120(): 
    ### var1
    data = [ 0L, 27021597764222992L, 0L, 0L]
    return data
_tokenSet_120 = antlr.BitSet(mk_tokenSet_120())

### generate bit set
def mk_tokenSet_121(): 
    ### var1
    data = [ 1342818400L, 9007198180999840L, 0L, 0L]
    return data
_tokenSet_121 = antlr.BitSet(mk_tokenSet_121())

### generate bit set
def mk_tokenSet_122(): 
    ### var1
    data = [ 1342818400L, 36028795945222832L, 0L, 0L]
    return data
_tokenSet_122 = antlr.BitSet(mk_tokenSet_122())

### generate bit set
def mk_tokenSet_123(): 
    ### var1
    data = [ 36028663874978304L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_123 = antlr.BitSet(mk_tokenSet_123())

### generate bit set
def mk_tokenSet_124(): 
    ### var1
    data = [ 1342818400L, 144115187002114736L, 0L, 0L]
    return data
_tokenSet_124 = antlr.BitSet(mk_tokenSet_124())

### generate bit set
def mk_tokenSet_125(): 
    ### var1
    data = [ 4359484027514913280L, -3458764513820540664L, 507905L, 0L, 0L, 0L]
    return data
_tokenSet_125 = antlr.BitSet(mk_tokenSet_125())

### generate bit set
def mk_tokenSet_126(): 
    ### var1
    data = [ 8971170047285119584L, -1073740808L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_126 = antlr.BitSet(mk_tokenSet_126())

### generate bit set
def mk_tokenSet_127(): 
    ### var1
    data = [ 0L, 6755399441056048L, 2L, 0L, 0L, 0L]
    return data
_tokenSet_127 = antlr.BitSet(mk_tokenSet_127())

### generate bit set
def mk_tokenSet_128(): 
    ### var1
    data = [ 0L, 1152921504606846976L, 8196L, 0L, 0L, 0L]
    return data
_tokenSet_128 = antlr.BitSet(mk_tokenSet_128())

### generate bit set
def mk_tokenSet_129(): 
    ### var1
    data = [ 4611686014937076608L, -2443202797848493704L, 516103L, 0L, 0L, 0L]
    return data
_tokenSet_129 = antlr.BitSet(mk_tokenSet_129())

### generate bit set
def mk_tokenSet_130(): 
    ### var1
    data = [ 36028247800021536L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_130 = antlr.BitSet(mk_tokenSet_130())

### generate bit set
def mk_tokenSet_131(): 
    ### var1
    data = [ 4323455642812809728L, 1152921504606847240L, 507904L, 0L, 0L, 0L]
    return data
_tokenSet_131 = antlr.BitSet(mk_tokenSet_131())

### generate bit set
def mk_tokenSet_132(): 
    ### var1
    data = [ 137438953472L, -4611686018427387904L, 1L, 0L, 0L, 0L]
    return data
_tokenSet_132 = antlr.BitSet(mk_tokenSet_132())

### generate bit set
def mk_tokenSet_133(): 
    ### var1
    data = [ 288230372661138304L, 1152921504606846976L, 0L, 0L]
    return data
_tokenSet_133 = antlr.BitSet(mk_tokenSet_133())

### generate bit set
def mk_tokenSet_134(): 
    ### var1
    data = [ 4611686016279633888L, 1297036691608962032L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_134 = antlr.BitSet(mk_tokenSet_134())

### generate bit set
def mk_tokenSet_135(): 
    ### var1
    data = [ 4611686020307077216L, 2882303760443376368L, 0L, 0L]
    return data
_tokenSet_135 = antlr.BitSet(mk_tokenSet_135())

### generate bit set
def mk_tokenSet_136(): 
    ### var1
    data = [ 100663808L, 1152921504606847088L, 8184L, 0L, 0L, 0L]
    return data
_tokenSet_136 = antlr.BitSet(mk_tokenSet_136())

### generate bit set
def mk_tokenSet_137(): 
    ### var1
    data = [ 4359484308131269216L, -2305843010287434760L, 524287L, 0L, 0L, 0L]
    return data
_tokenSet_137 = antlr.BitSet(mk_tokenSet_137())

### generate bit set
def mk_tokenSet_138(): 
    ### var1
    data = [ 1879689312L, 144115187002114736L, 0L, 0L]
    return data
_tokenSet_138 = antlr.BitSet(mk_tokenSet_138())
    
