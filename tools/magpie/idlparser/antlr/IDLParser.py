### $ANTLR 2.7.5 (20050403): "idl.g" -> "IDLParser.py"$
### import antlr and other modules ..
import sys
import antlr

version = sys.version.split()[0]
if version < '2.2.1':
    False = 0
if version < '2.3':
    True = not False
### header action >>> 
from extendAST import extendAST
### header action <<< 
### preamble action>>>

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
SEMI = 4
LITERAL_abstract = 5
LITERAL_local = 6
LITERAL_interface = 7
LITERAL_custom = 8
LITERAL_valuetype = 9
LITERAL_eventtype = 10
LBRACK = 11
COMMA = 12
RBRACK = 13
LPAREN = 14
RPAREN = 15
LITERAL_module = 16
LCURLY = 17
RCURLY = 18
COLON = 19
SCOPEOP = 20
IDENT = 21
LITERAL_truncatable = 22
LITERAL_supports = 23
LITERAL_public = 24
LITERAL_private = 25
LITERAL_factory = 26
LITERAL_in = 27
LITERAL_const = 28
ASSIGN = 29
OR = 30
XOR = 31
AND = 32
LSHIFT = 33
RSHIFT = 34
PLUS = 35
MINUS = 36
STAR = 37
DIV = 38
MOD = 39
TILDE = 40
LITERAL_TRUE = 41
LITERAL_FALSE = 42
LITERAL_typedef = 43
LITERAL_native = 44
LITERAL_float = 45
LITERAL_double = 46
LITERAL_long = 47
LITERAL_short = 48
LITERAL_unsigned = 49
LITERAL_char = 50
LITERAL_wchar = 51
LITERAL_boolean = 52
LITERAL_octet = 53
LITERAL_any = 54
LITERAL_Object = 55
LITERAL_struct = 56
LITERAL_union = 57
LITERAL_switch = 58
LITERAL_case = 59
LITERAL_default = 60
LITERAL_enum = 61
LITERAL_sequence = 62
LT = 63
GT = 64
LITERAL_string = 65
LITERAL_wstring = 66
LITERAL_exception = 67
LITERAL_oneway = 68
LITERAL_out = 69
LITERAL_inout = 70
LITERAL_raises = 71
LITERAL_context = 72
LITERAL_fixed = 73
LITERAL_ValueBase = 74
LITERAL_import = 75
LITERAL_typeid = 76
LITERAL_typeprefix = 77
LITERAL_readonly = 78
LITERAL_attribute = 79
LITERAL_getraises = 80
LITERAL_setraises = 81
LITERAL_component = 82
LITERAL_provides = 83
LITERAL_uses = 84
LITERAL_multiple = 85
LITERAL_emits = 86
LITERAL_publishes = 87
LITERAL_consumes = 88
LITERAL_home = 89
LITERAL_manages = 90
LITERAL_primarykey = 91
LITERAL_finder = 92
INT = 93
OCTAL = 94
HEX = 95
STRING_LITERAL = 96
WIDE_STRING_LITERAL = 97
CHAR_LITERAL = 98
WIDE_CHAR_LITERAL = 99
FIXED = 100
FLOAT = 101
QUESTION = 102
DOT = 103
NOT = 104
UNDERLINE = 105
WS = 106
PREPROC_DIRECTIVE = 107
SL_COMMENT = 108
ML_COMMENT = 109
ESC = 110
VOCAB = 111
DIGIT = 112
NONZERODIGIT = 113
OCTDIGIT = 114
HEXDIGIT = 115
ESCAPED_IDENT = 116

class Parser(antlr.LLkParser):
    ### user action >>>
    ### user action <<<
    
    def __init__(self, *args, **kwargs):
        antlr.LLkParser.__init__(self, *args, **kwargs)
        self.tokenNames = _tokenNames
        self.buildTokenTypeASTClassMap()
        self.astFactory = antlr.ASTFactory(self.getTokenTypeToASTClassMap())
        self.astFactory.setASTNodeClass()
        ### __init__ header action >>> 
        self.astFactory.setASTNodeClass(extendAST)
        ### __init__ header action <<< 
        
    def specification(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        specification_AST = None
        try:      ## for error handling
            pass
            while True:
                if (self.LA(1)==LITERAL_import):
                    pass
                    self.import_dcl()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            _cnt5= 0
            while True:
                if (_tokenSet_0.member(self.LA(1))):
                    pass
                    self.decorated_definition()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
                _cnt5 += 1
            if _cnt5 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            specification_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_1)
            else:
                raise ex
        
        self.returnAST = specification_AST
    
    def import_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        import_dcl_AST = None
        try:      ## for error handling
            pass
            tmp1_AST = None
            tmp1_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp1_AST)
            self.match(LITERAL_import)
            self.imported_scope()
            self.addASTChild(currentAST, self.returnAST)
            self.match(SEMI)
            import_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_2)
            else:
                raise ex
        
        self.returnAST = import_dcl_AST
    
    def decorated_definition(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        decorated_definition_AST = None
        try:      ## for error handling
            pass
            pass
            while True:
                if (self.LA(1)==LBRACK):
                    pass
                    self.decorator()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.definition()
            self.addASTChild(currentAST, self.returnAST)
            decorated_definition_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_3)
            else:
                raise ex
        
        self.returnAST = decorated_definition_AST
    
    def decorator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        decorator_AST = None
        try:      ## for error handling
            pass
            pass
            self.match(LBRACK)
            pass
            self.decorator_element()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.decorator_element()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RBRACK)
            decorator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_4)
            else:
                raise ex
        
        self.returnAST = decorator_AST
    
    def definition(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        definition_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_native,LITERAL_struct,LITERAL_union,LITERAL_enum]:
                pass
                self.type_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_const]:
                pass
                self.const_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_exception]:
                pass
                self.except_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_module]:
                pass
                self.module()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_typeid]:
                pass
                self.type_id_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_typeprefix]:
                pass
                self.type_prefix_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_component]:
                pass
                self.component()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_home]:
                pass
                self.home_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            else:
                synPredMatched14 = False
                if ((self.LA(1) >= LITERAL_abstract and self.LA(1) <= LITERAL_interface)) and (self.LA(2)==LITERAL_interface or self.LA(2)==IDENT) and (_tokenSet_5.member(self.LA(3))) and (_tokenSet_6.member(self.LA(4))):
                    _m14 = self.mark()
                    synPredMatched14 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        la1 = self.LA(1)
                        if False:
                            pass
                        elif la1 and la1 in [LITERAL_abstract]:
                            pass
                            self.match(LITERAL_abstract)
                        elif la1 and la1 in [LITERAL_local]:
                            pass
                            self.match(LITERAL_local)
                        elif la1 and la1 in [LITERAL_interface]:
                            pass
                        else:
                                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                            
                        self.match(LITERAL_interface)
                    except antlr.RecognitionException, pe:
                        synPredMatched14 = False
                    self.rewind(_m14)
                    self.inputState.guessing -= 1
                if synPredMatched14:
                    pass
                    self.interf()
                    self.addASTChild(currentAST, self.returnAST)
                    self.match(SEMI)
                else:
                    synPredMatched17 = False
                    if (self.LA(1)==LITERAL_abstract or self.LA(1)==LITERAL_custom or self.LA(1)==LITERAL_valuetype) and (self.LA(2)==LITERAL_valuetype or self.LA(2)==IDENT) and (_tokenSet_7.member(self.LA(3))) and (_tokenSet_8.member(self.LA(4))):
                        _m17 = self.mark()
                        synPredMatched17 = True
                        self.inputState.guessing += 1
                        try:
                            pass
                            la1 = self.LA(1)
                            if False:
                                pass
                            elif la1 and la1 in [LITERAL_abstract]:
                                pass
                                self.match(LITERAL_abstract)
                            elif la1 and la1 in [LITERAL_custom]:
                                pass
                                self.match(LITERAL_custom)
                            elif la1 and la1 in [LITERAL_valuetype]:
                                pass
                            else:
                                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                
                            self.match(LITERAL_valuetype)
                        except antlr.RecognitionException, pe:
                            synPredMatched17 = False
                        self.rewind(_m17)
                        self.inputState.guessing -= 1
                    if synPredMatched17:
                        pass
                        self.value()
                        self.addASTChild(currentAST, self.returnAST)
                        self.match(SEMI)
                    else:
                        synPredMatched20 = False
                        if (self.LA(1)==LITERAL_abstract or self.LA(1)==LITERAL_custom or self.LA(1)==LITERAL_eventtype) and (self.LA(2)==LITERAL_eventtype or self.LA(2)==IDENT) and (_tokenSet_9.member(self.LA(3))) and (_tokenSet_10.member(self.LA(4))):
                            _m20 = self.mark()
                            synPredMatched20 = True
                            self.inputState.guessing += 1
                            try:
                                pass
                                la1 = self.LA(1)
                                if False:
                                    pass
                                elif la1 and la1 in [LITERAL_abstract]:
                                    pass
                                    self.match(LITERAL_abstract)
                                elif la1 and la1 in [LITERAL_custom]:
                                    pass
                                    self.match(LITERAL_custom)
                                elif la1 and la1 in [LITERAL_eventtype]:
                                    pass
                                else:
                                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                                    
                                self.match(LITERAL_eventtype)
                            except antlr.RecognitionException, pe:
                                synPredMatched20 = False
                            self.rewind(_m20)
                            self.inputState.guessing -= 1
                        if synPredMatched20:
                            pass
                            self.event()
                            self.addASTChild(currentAST, self.returnAST)
                            self.match(SEMI)
                        else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
            definition_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_11)
            else:
                raise ex
        
        self.returnAST = definition_AST
    
    def type_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        type_dcl_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef]:
                pass
                tmp17_AST = None
                tmp17_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp17_AST)
                self.match(LITERAL_typedef)
                self.type_declarator()
                self.addASTChild(currentAST, self.returnAST)
                type_dcl_AST = currentAST.root
            elif la1 and la1 in [LITERAL_enum]:
                pass
                self.enum_type()
                self.addASTChild(currentAST, self.returnAST)
                type_dcl_AST = currentAST.root
            elif la1 and la1 in [LITERAL_native]:
                pass
                tmp18_AST = None
                tmp18_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp18_AST)
                self.match(LITERAL_native)
                self.simple_declarator()
                self.addASTChild(currentAST, self.returnAST)
                type_dcl_AST = currentAST.root
            else:
                synPredMatched131 = False
                if (self.LA(1)==LITERAL_struct) and (self.LA(2)==IDENT) and (self.LA(3)==LCURLY):
                    _m131 = self.mark()
                    synPredMatched131 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.struct_type()
                    except antlr.RecognitionException, pe:
                        synPredMatched131 = False
                    self.rewind(_m131)
                    self.inputState.guessing -= 1
                if synPredMatched131:
                    pass
                    self.struct_type()
                    self.addASTChild(currentAST, self.returnAST)
                    type_dcl_AST = currentAST.root
                else:
                    synPredMatched133 = False
                    if (self.LA(1)==LITERAL_union) and (self.LA(2)==IDENT) and (self.LA(3)==LITERAL_switch):
                        _m133 = self.mark()
                        synPredMatched133 = True
                        self.inputState.guessing += 1
                        try:
                            pass
                            self.union_type()
                        except antlr.RecognitionException, pe:
                            synPredMatched133 = False
                        self.rewind(_m133)
                        self.inputState.guessing -= 1
                    if synPredMatched133:
                        pass
                        self.union_type()
                        self.addASTChild(currentAST, self.returnAST)
                        type_dcl_AST = currentAST.root
                    elif (self.LA(1)==LITERAL_struct or self.LA(1)==LITERAL_union) and (self.LA(2)==IDENT) and (self.LA(3)==SEMI):
                        pass
                        self.constr_forward_decl()
                        self.addASTChild(currentAST, self.returnAST)
                        type_dcl_AST = currentAST.root
                    else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = type_dcl_AST
    
    def const_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        const_dcl_AST = None
        try:      ## for error handling
            pass
            tmp19_AST = None
            tmp19_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp19_AST)
            self.match(LITERAL_const)
            self.const_type()
            self.addASTChild(currentAST, self.returnAST)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(ASSIGN)
            self.const_exp()
            self.addASTChild(currentAST, self.returnAST)
            const_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = const_dcl_AST
    
    def except_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        except_dcl_AST = None
        try:      ## for error handling
            pass
            tmp21_AST = None
            tmp21_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp21_AST)
            self.match(LITERAL_exception)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            self.opt_member_list()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            except_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = except_dcl_AST
    
    def interf(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interf_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_abstract]:
                pass
                tmp24_AST = None
                tmp24_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp24_AST)
                self.match(LITERAL_abstract)
            elif la1 and la1 in [LITERAL_local]:
                pass
                tmp25_AST = None
                tmp25_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp25_AST)
                self.match(LITERAL_local)
            elif la1 and la1 in [LITERAL_interface]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            tmp26_AST = None
            tmp26_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp26_AST)
            self.match(LITERAL_interface)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY,COLON]:
                pass
                self.interface_dcl()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            interf_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = interf_AST
    
    def module(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        module_AST = None
        d_AST = None
        try:      ## for error handling
            pass
            tmp27_AST = None
            tmp27_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp27_AST)
            self.match(LITERAL_module)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            self.definition_list()
            d_AST = self.returnAST
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            module_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = module_AST
    
    def value(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_abstract]:
                pass
                self.value_abs_dcl()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_custom]:
                pass
                self.value_custom_dcl()
                self.addASTChild(currentAST, self.returnAST)
            else:
                if (self.LA(1)==LITERAL_valuetype) and (self.LA(2)==IDENT) and (self.LA(3)==LCURLY or self.LA(3)==COLON or self.LA(3)==LITERAL_supports):
                    pass
                    self.value_dcl()
                    self.addASTChild(currentAST, self.returnAST)
                elif (self.LA(1)==LITERAL_valuetype) and (self.LA(2)==IDENT) and (_tokenSet_13.member(self.LA(3))):
                    pass
                    self.value_box_dcl()
                    self.addASTChild(currentAST, self.returnAST)
                elif (self.LA(1)==LITERAL_valuetype) and (self.LA(2)==IDENT) and (self.LA(3)==SEMI):
                    pass
                    self.value_forward_dcl()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            value_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_AST
    
    def type_id_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        type_id_dcl_AST = None
        try:      ## for error handling
            pass
            tmp30_AST = None
            tmp30_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp30_AST)
            self.match(LITERAL_typeid)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            self.string_literal()
            self.addASTChild(currentAST, self.returnAST)
            type_id_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = type_id_dcl_AST
    
    def type_prefix_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        type_prefix_dcl_AST = None
        try:      ## for error handling
            pass
            tmp31_AST = None
            tmp31_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp31_AST)
            self.match(LITERAL_typeprefix)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            self.string_literal()
            self.addASTChild(currentAST, self.returnAST)
            type_prefix_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = type_prefix_dcl_AST
    
    def event(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_abstract]:
                pass
                self.event_abs()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_custom]:
                pass
                self.event_custom()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_eventtype]:
                pass
                self.event_dcl()
                self.addASTChild(currentAST, self.returnAST)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            event_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = event_AST
    
    def component(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        component_AST = None
        try:      ## for error handling
            pass
            tmp32_AST = None
            tmp32_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp32_AST)
            self.match(LITERAL_component)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY,COLON,LITERAL_supports]:
                pass
                self.component_dcl()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            component_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = component_AST
    
    def home_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        home_dcl_AST = None
        try:      ## for error handling
            pass
            self.home_header()
            self.addASTChild(currentAST, self.returnAST)
            self.home_body()
            self.addASTChild(currentAST, self.returnAST)
            home_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = home_dcl_AST
    
    def decorator_element(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        decorator_element_AST = None
        try:      ## for error handling
            pass
            pass
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LPAREN]:
                pass
                self.match(LPAREN)
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LPAREN,SCOPEOP,IDENT,PLUS,MINUS,TILDE,LITERAL_TRUE,LITERAL_FALSE,INT,OCTAL,HEX,STRING_LITERAL,WIDE_STRING_LITERAL,CHAR_LITERAL,WIDE_CHAR_LITERAL,FIXED,FLOAT]:
                    pass
                    self.expr_list()
                    self.addASTChild(currentAST, self.returnAST)
                elif la1 and la1 in [RPAREN]:
                    pass
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.match(RPAREN)
            elif la1 and la1 in [COMMA,RBRACK]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            decorator_element_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_14)
            else:
                raise ex
        
        self.returnAST = decorator_element_AST
    
    def identifier(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        identifier_AST = None
        try:      ## for error handling
            pass
            tmp35_AST = None
            tmp35_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp35_AST)
            self.match(IDENT)
            identifier_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_15)
            else:
                raise ex
        
        self.returnAST = identifier_AST
    
    def expr_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        expr_list_AST = None
        try:      ## for error handling
            pass
            pass
            pass
            self.const_exp()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    pass
                    self.const_exp()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            expr_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_16)
            else:
                raise ex
        
        self.returnAST = expr_list_AST
    
    def const_exp(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        const_exp_AST = None
        try:      ## for error handling
            pass
            self.or_expr()
            self.addASTChild(currentAST, self.returnAST)
            const_exp_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        self.returnAST = const_exp_AST
    
    def definition_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        definition_list_AST = None
        try:      ## for error handling
            pass
            _cnt39= 0
            while True:
                if (_tokenSet_18.member(self.LA(1))):
                    pass
                    self.definition()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
                _cnt39 += 1
            if _cnt39 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            definition_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = definition_list_AST
    
    def interface_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interface_dcl_AST = None
        try:      ## for error handling
            pass
            self.interface_header()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            self.interface_body()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            interface_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = interface_dcl_AST
    
    def interface_header(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interface_header_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [COLON]:
                pass
                self.interface_inheritance_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            interface_header_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = interface_header_AST
    
    def interface_body(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interface_body_AST = None
        try:      ## for error handling
            pass
            while True:
                if (_tokenSet_21.member(self.LA(1))):
                    pass
                    self.export()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            interface_body_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = interface_body_AST
    
    def interface_inheritance_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interface_inheritance_spec_AST = None
        try:      ## for error handling
            pass
            tmp39_AST = None
            tmp39_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp39_AST)
            self.match(COLON)
            self.scoped_name_list()
            self.addASTChild(currentAST, self.returnAST)
            interface_inheritance_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = interface_inheritance_spec_AST
    
    def export(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        export_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_typedef,LITERAL_native,LITERAL_struct,LITERAL_union,LITERAL_enum]:
                pass
                self.type_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_const]:
                pass
                self.const_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_exception]:
                pass
                self.except_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_readonly,LITERAL_attribute]:
                pass
                self.attr_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LBRACK,SCOPEOP,IDENT,LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_string,LITERAL_wstring,LITERAL_oneway,LITERAL_ValueBase]:
                pass
                self.op_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_typeid]:
                pass
                self.type_id_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_typeprefix]:
                pass
                self.type_prefix_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            export_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_22)
            else:
                raise ex
        
        self.returnAST = export_AST
    
    def attr_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        attr_dcl_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_readonly]:
                pass
                self.readonly_attr_spec()
                self.addASTChild(currentAST, self.returnAST)
                attr_dcl_AST = currentAST.root
            elif la1 and la1 in [LITERAL_attribute]:
                pass
                self.attr_spec()
                self.addASTChild(currentAST, self.returnAST)
                attr_dcl_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = attr_dcl_AST
    
    def op_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        op_dcl_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LBRACK]:
                pass
                self.decorator()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SCOPEOP,IDENT,LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_string,LITERAL_wstring,LITERAL_oneway,LITERAL_ValueBase]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_oneway]:
                pass
                self.op_attribute()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SCOPEOP,IDENT,LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_string,LITERAL_wstring,LITERAL_ValueBase]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.op_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            tmp47_AST = None
            tmp47_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp47_AST)
            self.match(IDENT)
            self.parameter_dcls()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_raises]:
                pass
                self.raises_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI,LITERAL_context]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_context]:
                pass
                self.context_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            op_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = op_dcl_AST
    
    def scoped_name_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        scoped_name_list_AST = None
        try:      ## for error handling
            pass
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.scoped_name()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            scoped_name_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_23)
            else:
                raise ex
        
        self.returnAST = scoped_name_list_AST
    
    def interface_name(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interface_name_AST = None
        try:      ## for error handling
            pass
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            interface_name_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_24)
            else:
                raise ex
        
        self.returnAST = interface_name_AST
    
    def scoped_name(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        scoped_name_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [SCOPEOP]:
                pass
                tmp49_AST = None
                tmp49_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp49_AST)
                self.match(SCOPEOP)
            elif la1 and la1 in [IDENT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            tmp50_AST = None
            tmp50_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp50_AST)
            self.match(IDENT)
            while True:
                if (self.LA(1)==SCOPEOP):
                    pass
                    self.match(SCOPEOP)
                    self.identifier()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            scoped_name_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_25)
            else:
                raise ex
        
        self.returnAST = scoped_name_AST
    
    def value_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_dcl_AST = None
        try:      ## for error handling
            pass
            self.value_header()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            while True:
                if (_tokenSet_26.member(self.LA(1))):
                    pass
                    self.value_element()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RCURLY)
            value_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_dcl_AST
    
    def value_abs_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_abs_dcl_AST = None
        try:      ## for error handling
            pass
            tmp54_AST = None
            tmp54_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp54_AST)
            self.match(LITERAL_abstract)
            tmp55_AST = None
            tmp55_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp55_AST)
            self.match(LITERAL_valuetype)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY,COLON,LITERAL_supports]:
                pass
                self.value_abs_full_dcl()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            value_abs_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_abs_dcl_AST
    
    def value_box_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_box_dcl_AST = None
        try:      ## for error handling
            pass
            tmp56_AST = None
            tmp56_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp56_AST)
            self.match(LITERAL_valuetype)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.type_spec()
            self.addASTChild(currentAST, self.returnAST)
            value_box_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_box_dcl_AST
    
    def value_custom_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_custom_dcl_AST = None
        try:      ## for error handling
            pass
            tmp57_AST = None
            tmp57_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp57_AST)
            self.match(LITERAL_custom)
            self.value_dcl()
            self.addASTChild(currentAST, self.returnAST)
            value_custom_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_custom_dcl_AST
    
    def value_forward_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_forward_dcl_AST = None
        try:      ## for error handling
            pass
            tmp58_AST = None
            tmp58_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp58_AST)
            self.match(LITERAL_valuetype)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            value_forward_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_forward_dcl_AST
    
    def type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [SCOPEOP,IDENT,LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_sequence,LITERAL_string,LITERAL_wstring,LITERAL_fixed,LITERAL_ValueBase]:
                pass
                self.simple_type_spec()
                self.addASTChild(currentAST, self.returnAST)
                type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_struct,LITERAL_union,LITERAL_enum]:
                pass
                self.constr_type_spec()
                self.addASTChild(currentAST, self.returnAST)
                type_spec_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_27)
            else:
                raise ex
        
        self.returnAST = type_spec_AST
    
    def value_abs_full_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_abs_full_dcl_AST = None
        try:      ## for error handling
            pass
            self.value_inheritance_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            while True:
                if (_tokenSet_21.member(self.LA(1))):
                    pass
                    self.export()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RCURLY)
            value_abs_full_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = value_abs_full_dcl_AST
    
    def value_inheritance_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_inheritance_spec_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [COLON]:
                pass
                self.value_value_inheritance_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LCURLY,LITERAL_supports]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_supports]:
                pass
                self.value_interface_inheritance_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            value_inheritance_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = value_inheritance_spec_AST
    
    def value_header(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_header_AST = None
        try:      ## for error handling
            pass
            tmp61_AST = None
            tmp61_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp61_AST)
            self.match(LITERAL_valuetype)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.value_inheritance_spec()
            self.addASTChild(currentAST, self.returnAST)
            value_header_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = value_header_AST
    
    def value_element(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_element_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LBRACK,SCOPEOP,IDENT,LITERAL_const,LITERAL_typedef,LITERAL_native,LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_struct,LITERAL_union,LITERAL_enum,LITERAL_string,LITERAL_wstring,LITERAL_exception,LITERAL_oneway,LITERAL_ValueBase,LITERAL_typeid,LITERAL_typeprefix,LITERAL_readonly,LITERAL_attribute]:
                pass
                self.export()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_public,LITERAL_private]:
                pass
                self.state_member()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_factory]:
                pass
                self.init_dcl()
                self.addASTChild(currentAST, self.returnAST)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            value_element_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_28)
            else:
                raise ex
        
        self.returnAST = value_element_AST
    
    def value_value_inheritance_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_value_inheritance_spec_AST = None
        try:      ## for error handling
            pass
            tmp62_AST = None
            tmp62_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp62_AST)
            self.match(COLON)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_truncatable]:
                pass
                tmp63_AST = None
                tmp63_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp63_AST)
                self.match(LITERAL_truncatable)
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.value_name()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.value_name()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            value_value_inheritance_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_29)
            else:
                raise ex
        
        self.returnAST = value_value_inheritance_spec_AST
    
    def value_interface_inheritance_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_interface_inheritance_spec_AST = None
        try:      ## for error handling
            pass
            tmp65_AST = None
            tmp65_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp65_AST)
            self.match(LITERAL_supports)
            self.interface_name()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.interface_name()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            value_interface_inheritance_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = value_interface_inheritance_spec_AST
    
    def value_name(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_name_AST = None
        try:      ## for error handling
            pass
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            value_name_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_30)
            else:
                raise ex
        
        self.returnAST = value_name_AST
    
    def state_member(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        state_member_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_public]:
                pass
                tmp67_AST = None
                tmp67_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp67_AST)
                self.match(LITERAL_public)
            elif la1 and la1 in [LITERAL_private]:
                pass
                tmp68_AST = None
                tmp68_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp68_AST)
                self.match(LITERAL_private)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.declarators()
            self.addASTChild(currentAST, self.returnAST)
            self.match(SEMI)
            state_member_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_28)
            else:
                raise ex
        
        self.returnAST = state_member_AST
    
    def init_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        init_dcl_AST = None
        try:      ## for error handling
            pass
            tmp70_AST = None
            tmp70_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp70_AST)
            self.match(LITERAL_factory)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_in]:
                pass
                self.init_param_decls()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_raises]:
                pass
                self.raises_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(SEMI)
            init_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_28)
            else:
                raise ex
        
        self.returnAST = init_dcl_AST
    
    def declarators(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        declarators_AST = None
        try:      ## for error handling
            pass
            self.declarator()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.declarator()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            declarators_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = declarators_AST
    
    def init_param_decls(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        init_param_decls_AST = None
        try:      ## for error handling
            pass
            self.init_param_decl()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.init_param_decl()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            init_param_decls_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_16)
            else:
                raise ex
        
        self.returnAST = init_param_decls_AST
    
    def raises_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        raises_expr_AST = None
        try:      ## for error handling
            pass
            tmp76_AST = None
            tmp76_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp76_AST)
            self.match(LITERAL_raises)
            self.match(LPAREN)
            self.scoped_name_list()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RPAREN)
            raises_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_31)
            else:
                raise ex
        
        self.returnAST = raises_expr_AST
    
    def init_param_decl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        init_param_decl_AST = None
        try:      ## for error handling
            pass
            self.init_param_attribute()
            self.addASTChild(currentAST, self.returnAST)
            self.param_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.simple_declarator()
            self.addASTChild(currentAST, self.returnAST)
            init_param_decl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_32)
            else:
                raise ex
        
        self.returnAST = init_param_decl_AST
    
    def init_param_attribute(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        init_param_attribute_AST = None
        try:      ## for error handling
            pass
            tmp79_AST = None
            tmp79_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp79_AST)
            self.match(LITERAL_in)
            init_param_attribute_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_33)
            else:
                raise ex
        
        self.returnAST = init_param_attribute_AST
    
    def param_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        param_type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_ValueBase]:
                pass
                self.base_type_spec()
                self.addASTChild(currentAST, self.returnAST)
                param_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_string]:
                pass
                self.string_type()
                self.addASTChild(currentAST, self.returnAST)
                param_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_wstring]:
                pass
                self.wide_string_type()
                self.addASTChild(currentAST, self.returnAST)
                param_type_spec_AST = currentAST.root
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
                param_type_spec_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_34)
            else:
                raise ex
        
        self.returnAST = param_type_spec_AST
    
    def simple_declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        simple_declarator_AST = None
        try:      ## for error handling
            pass
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            simple_declarator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_35)
            else:
                raise ex
        
        self.returnAST = simple_declarator_AST
    
    def const_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        const_type_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_char]:
                pass
                self.char_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_wchar]:
                pass
                self.wide_char_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_boolean]:
                pass
                self.boolean_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_string]:
                pass
                self.string_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_wstring]:
                pass
                self.wide_string_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_fixed]:
                pass
                self.fixed_pt_const_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_octet]:
                pass
                self.octet_type()
                self.addASTChild(currentAST, self.returnAST)
                const_type_AST = currentAST.root
            else:
                synPredMatched100 = False
                if ((self.LA(1) >= LITERAL_long and self.LA(1) <= LITERAL_unsigned)) and (self.LA(2)==IDENT or self.LA(2)==LITERAL_long or self.LA(2)==LITERAL_short) and (self.LA(3)==IDENT or self.LA(3)==ASSIGN or self.LA(3)==LITERAL_long) and (_tokenSet_36.member(self.LA(4))):
                    _m100 = self.mark()
                    synPredMatched100 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.integer_type()
                    except antlr.RecognitionException, pe:
                        synPredMatched100 = False
                    self.rewind(_m100)
                    self.inputState.guessing -= 1
                if synPredMatched100:
                    pass
                    self.integer_type()
                    self.addASTChild(currentAST, self.returnAST)
                    const_type_AST = currentAST.root
                elif ((self.LA(1) >= LITERAL_float and self.LA(1) <= LITERAL_long)) and (self.LA(2)==IDENT or self.LA(2)==LITERAL_double) and (self.LA(3)==IDENT or self.LA(3)==ASSIGN) and (_tokenSet_36.member(self.LA(4))):
                    pass
                    self.floating_pt_type()
                    self.addASTChild(currentAST, self.returnAST)
                    const_type_AST = currentAST.root
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_37)
            else:
                raise ex
        
        self.returnAST = const_type_AST
    
    def integer_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        integer_type_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_long,LITERAL_short]:
                pass
                self.signed_int()
                self.addASTChild(currentAST, self.returnAST)
                integer_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_unsigned]:
                pass
                self.unsigned_int()
                self.addASTChild(currentAST, self.returnAST)
                integer_type_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = integer_type_AST
    
    def char_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        char_type_AST = None
        try:      ## for error handling
            pass
            tmp80_AST = None
            tmp80_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp80_AST)
            self.match(LITERAL_char)
            char_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = char_type_AST
    
    def wide_char_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        wide_char_type_AST = None
        try:      ## for error handling
            pass
            tmp81_AST = None
            tmp81_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp81_AST)
            self.match(LITERAL_wchar)
            wide_char_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = wide_char_type_AST
    
    def boolean_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        boolean_type_AST = None
        try:      ## for error handling
            pass
            tmp82_AST = None
            tmp82_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp82_AST)
            self.match(LITERAL_boolean)
            boolean_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = boolean_type_AST
    
    def floating_pt_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        floating_pt_type_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_float]:
                pass
                tmp83_AST = None
                tmp83_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp83_AST)
                self.match(LITERAL_float)
                floating_pt_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_double]:
                pass
                tmp84_AST = None
                tmp84_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp84_AST)
                self.match(LITERAL_double)
                floating_pt_type_AST = currentAST.root
            elif la1 and la1 in [LITERAL_long]:
                pass
                tmp85_AST = None
                tmp85_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp85_AST)
                self.match(LITERAL_long)
                tmp86_AST = None
                tmp86_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp86_AST)
                self.match(LITERAL_double)
                floating_pt_type_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = floating_pt_type_AST
    
    def string_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        string_type_AST = None
        try:      ## for error handling
            pass
            tmp87_AST = None
            tmp87_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp87_AST)
            self.match(LITERAL_string)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LT]:
                pass
                self.match(LT)
                self.positive_int_const()
                self.addASTChild(currentAST, self.returnAST)
                self.match(GT)
            elif la1 and la1 in [SEMI,COMMA,IDENT,STAR,GT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            string_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = string_type_AST
    
    def wide_string_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        wide_string_type_AST = None
        try:      ## for error handling
            pass
            tmp90_AST = None
            tmp90_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp90_AST)
            self.match(LITERAL_wstring)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LT]:
                pass
                self.match(LT)
                self.positive_int_const()
                self.addASTChild(currentAST, self.returnAST)
                self.match(GT)
            elif la1 and la1 in [SEMI,COMMA,IDENT,STAR,GT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            wide_string_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = wide_string_type_AST
    
    def fixed_pt_const_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        fixed_pt_const_type_AST = None
        try:      ## for error handling
            pass
            tmp93_AST = None
            tmp93_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp93_AST)
            self.match(LITERAL_fixed)
            fixed_pt_const_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_37)
            else:
                raise ex
        
        self.returnAST = fixed_pt_const_type_AST
    
    def octet_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        octet_type_AST = None
        try:      ## for error handling
            pass
            tmp94_AST = None
            tmp94_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp94_AST)
            self.match(LITERAL_octet)
            octet_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = octet_type_AST
    
    def or_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        or_expr_AST = None
        try:      ## for error handling
            pass
            self.xor_expr()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==OR):
                    pass
                    tmp95_AST = None
                    tmp95_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp95_AST)
                    self.match(OR)
                    self.xor_expr()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            or_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_17)
            else:
                raise ex
        
        self.returnAST = or_expr_AST
    
    def xor_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        xor_expr_AST = None
        try:      ## for error handling
            pass
            self.and_expr()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==XOR):
                    pass
                    tmp96_AST = None
                    tmp96_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp96_AST)
                    self.match(XOR)
                    self.and_expr()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            xor_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_40)
            else:
                raise ex
        
        self.returnAST = xor_expr_AST
    
    def and_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        and_expr_AST = None
        try:      ## for error handling
            pass
            self.shift_expr()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==AND):
                    pass
                    tmp97_AST = None
                    tmp97_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp97_AST)
                    self.match(AND)
                    self.shift_expr()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            and_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_41)
            else:
                raise ex
        
        self.returnAST = and_expr_AST
    
    def shift_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        shift_expr_AST = None
        try:      ## for error handling
            pass
            self.add_expr()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==LSHIFT or self.LA(1)==RSHIFT):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LSHIFT]:
                        pass
                        tmp98_AST = None
                        tmp98_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp98_AST)
                        self.match(LSHIFT)
                    elif la1 and la1 in [RSHIFT]:
                        pass
                        tmp99_AST = None
                        tmp99_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp99_AST)
                        self.match(RSHIFT)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.add_expr()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            shift_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_42)
            else:
                raise ex
        
        self.returnAST = shift_expr_AST
    
    def add_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        add_expr_AST = None
        try:      ## for error handling
            pass
            self.mult_expr()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==PLUS or self.LA(1)==MINUS):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [PLUS]:
                        pass
                        tmp100_AST = None
                        tmp100_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp100_AST)
                        self.match(PLUS)
                    elif la1 and la1 in [MINUS]:
                        pass
                        tmp101_AST = None
                        tmp101_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp101_AST)
                        self.match(MINUS)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.mult_expr()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            add_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_43)
            else:
                raise ex
        
        self.returnAST = add_expr_AST
    
    def mult_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        mult_expr_AST = None
        try:      ## for error handling
            pass
            self.unary_expr()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if ((self.LA(1) >= STAR and self.LA(1) <= MOD)):
                    pass
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [STAR]:
                        pass
                        tmp102_AST = None
                        tmp102_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp102_AST)
                        self.match(STAR)
                    elif la1 and la1 in [DIV]:
                        pass
                        tmp103_AST = None
                        tmp103_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp103_AST)
                        self.match(DIV)
                    elif la1 and la1 in [MOD]:
                        pass
                        tmp104_AST = None
                        tmp104_AST = self.astFactory.create(self.LT(1))
                        self.addASTChild(currentAST, tmp104_AST)
                        self.match(MOD)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.unary_expr()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            mult_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_44)
            else:
                raise ex
        
        self.returnAST = mult_expr_AST
    
    def unary_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        unary_expr_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [PLUS,MINUS,TILDE]:
                pass
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [MINUS]:
                    pass
                    tmp105_AST = None
                    tmp105_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp105_AST)
                    self.match(MINUS)
                elif la1 and la1 in [PLUS]:
                    pass
                    tmp106_AST = None
                    tmp106_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp106_AST)
                    self.match(PLUS)
                elif la1 and la1 in [TILDE]:
                    pass
                    tmp107_AST = None
                    tmp107_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp107_AST)
                    self.match(TILDE)
                else:
                        raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                    
                self.primary_expr()
                self.addASTChild(currentAST, self.returnAST)
                unary_expr_AST = currentAST.root
            elif la1 and la1 in [LPAREN,SCOPEOP,IDENT,LITERAL_TRUE,LITERAL_FALSE,INT,OCTAL,HEX,STRING_LITERAL,WIDE_STRING_LITERAL,CHAR_LITERAL,WIDE_CHAR_LITERAL,FIXED,FLOAT]:
                pass
                self.primary_expr()
                self.addASTChild(currentAST, self.returnAST)
                unary_expr_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = unary_expr_AST
    
    def primary_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        primary_expr_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
                primary_expr_AST = currentAST.root
            elif la1 and la1 in [LITERAL_TRUE,LITERAL_FALSE,INT,OCTAL,HEX,STRING_LITERAL,WIDE_STRING_LITERAL,CHAR_LITERAL,WIDE_CHAR_LITERAL,FIXED,FLOAT]:
                pass
                self.literal()
                self.addASTChild(currentAST, self.returnAST)
                primary_expr_AST = currentAST.root
            elif la1 and la1 in [LPAREN]:
                pass
                tmp108_AST = None
                tmp108_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp108_AST)
                self.match(LPAREN)
                self.const_exp()
                self.addASTChild(currentAST, self.returnAST)
                tmp109_AST = None
                tmp109_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp109_AST)
                self.match(RPAREN)
                primary_expr_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = primary_expr_AST
    
    def literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        literal_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [INT,OCTAL,HEX]:
                pass
                self.integer_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [STRING_LITERAL]:
                pass
                self.string_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [WIDE_STRING_LITERAL]:
                pass
                self.wide_string_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [CHAR_LITERAL]:
                pass
                self.character_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [WIDE_CHAR_LITERAL]:
                pass
                self.wide_character_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [FIXED]:
                pass
                self.fixed_pt_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [FLOAT]:
                pass
                self.floating_pt_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            elif la1 and la1 in [LITERAL_TRUE,LITERAL_FALSE]:
                pass
                self.boolean_literal()
                self.addASTChild(currentAST, self.returnAST)
                literal_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = literal_AST
    
    def integer_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        integer_literal_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [INT]:
                pass
                tmp110_AST = None
                tmp110_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp110_AST)
                self.match(INT)
                integer_literal_AST = currentAST.root
            elif la1 and la1 in [OCTAL]:
                pass
                tmp111_AST = None
                tmp111_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp111_AST)
                self.match(OCTAL)
                integer_literal_AST = currentAST.root
            elif la1 and la1 in [HEX]:
                pass
                tmp112_AST = None
                tmp112_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp112_AST)
                self.match(HEX)
                integer_literal_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = integer_literal_AST
    
    def string_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        string_literal_AST = None
        try:      ## for error handling
            pass
            _cnt310= 0
            while True:
                if (self.LA(1)==STRING_LITERAL):
                    pass
                    tmp113_AST = None
                    tmp113_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp113_AST)
                    self.match(STRING_LITERAL)
                else:
                    break
                
                _cnt310 += 1
            if _cnt310 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            string_literal_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = string_literal_AST
    
    def wide_string_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        wide_string_literal_AST = None
        try:      ## for error handling
            pass
            _cnt313= 0
            while True:
                if (self.LA(1)==WIDE_STRING_LITERAL):
                    pass
                    tmp114_AST = None
                    tmp114_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp114_AST)
                    self.match(WIDE_STRING_LITERAL)
                else:
                    break
                
                _cnt313 += 1
            if _cnt313 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            wide_string_literal_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = wide_string_literal_AST
    
    def character_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        character_literal_AST = None
        try:      ## for error handling
            pass
            tmp115_AST = None
            tmp115_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp115_AST)
            self.match(CHAR_LITERAL)
            character_literal_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = character_literal_AST
    
    def wide_character_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        wide_character_literal_AST = None
        try:      ## for error handling
            pass
            tmp116_AST = None
            tmp116_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp116_AST)
            self.match(WIDE_CHAR_LITERAL)
            wide_character_literal_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = wide_character_literal_AST
    
    def fixed_pt_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        fixed_pt_literal_AST = None
        try:      ## for error handling
            pass
            tmp117_AST = None
            tmp117_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp117_AST)
            self.match(FIXED)
            fixed_pt_literal_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = fixed_pt_literal_AST
    
    def floating_pt_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        floating_pt_literal_AST = None
        f = None
        f_AST = None
        try:      ## for error handling
            pass
            f = self.LT(1)
            f_AST = self.astFactory.create(f)
            self.addASTChild(currentAST, f_AST)
            self.match(FLOAT)
            floating_pt_literal_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = floating_pt_literal_AST
    
    def boolean_literal(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        boolean_literal_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_TRUE]:
                pass
                tmp118_AST = None
                tmp118_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp118_AST)
                self.match(LITERAL_TRUE)
                boolean_literal_AST = currentAST.root
            elif la1 and la1 in [LITERAL_FALSE]:
                pass
                tmp119_AST = None
                tmp119_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp119_AST)
                self.match(LITERAL_FALSE)
                boolean_literal_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_45)
            else:
                raise ex
        
        self.returnAST = boolean_literal_AST
    
    def positive_int_const(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        positive_int_const_AST = None
        try:      ## for error handling
            pass
            self.const_exp()
            self.addASTChild(currentAST, self.returnAST)
            positive_int_const_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_46)
            else:
                raise ex
        
        self.returnAST = positive_int_const_AST
    
    def type_declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        type_declarator_AST = None
        try:      ## for error handling
            pass
            self.type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.declarators()
            self.addASTChild(currentAST, self.returnAST)
            type_declarator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = type_declarator_AST
    
    def struct_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        struct_type_AST = None
        try:      ## for error handling
            pass
            tmp120_AST = None
            tmp120_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp120_AST)
            self.match(LITERAL_struct)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            self.member_list()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            struct_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_27)
            else:
                raise ex
        
        self.returnAST = struct_type_AST
    
    def union_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        union_type_AST = None
        try:      ## for error handling
            pass
            tmp123_AST = None
            tmp123_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp123_AST)
            self.match(LITERAL_union)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LITERAL_switch)
            self.match(LPAREN)
            self.switch_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RPAREN)
            self.match(LCURLY)
            self.switch_body()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            union_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_27)
            else:
                raise ex
        
        self.returnAST = union_type_AST
    
    def enum_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        enum_type_AST = None
        try:      ## for error handling
            pass
            tmp129_AST = None
            tmp129_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp129_AST)
            self.match(LITERAL_enum)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            self.enumerator_list()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            enum_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_47)
            else:
                raise ex
        
        self.returnAST = enum_type_AST
    
    def constr_forward_decl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        constr_forward_decl_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_struct]:
                pass
                tmp132_AST = None
                tmp132_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp132_AST)
                self.match(LITERAL_struct)
                self.identifier()
                self.addASTChild(currentAST, self.returnAST)
                constr_forward_decl_AST = currentAST.root
            elif la1 and la1 in [LITERAL_union]:
                pass
                tmp133_AST = None
                tmp133_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp133_AST)
                self.match(LITERAL_union)
                self.identifier()
                self.addASTChild(currentAST, self.returnAST)
                constr_forward_decl_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = constr_forward_decl_AST
    
    def simple_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        simple_type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_ValueBase]:
                pass
                self.base_type_spec()
                self.addASTChild(currentAST, self.returnAST)
                simple_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_sequence,LITERAL_string,LITERAL_wstring,LITERAL_fixed]:
                pass
                self.template_type_spec()
                self.addASTChild(currentAST, self.returnAST)
                simple_type_spec_AST = currentAST.root
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
                simple_type_spec_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_48)
            else:
                raise ex
        
        self.returnAST = simple_type_spec_AST
    
    def constr_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        constr_type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_struct]:
                pass
                self.struct_type()
                self.addASTChild(currentAST, self.returnAST)
                constr_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_union]:
                pass
                self.union_type()
                self.addASTChild(currentAST, self.returnAST)
                constr_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_enum]:
                pass
                self.enum_type()
                self.addASTChild(currentAST, self.returnAST)
                constr_type_spec_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_27)
            else:
                raise ex
        
        self.returnAST = constr_type_spec_AST
    
    def base_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        base_type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_char]:
                pass
                self.char_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_wchar]:
                pass
                self.wide_char_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_boolean]:
                pass
                self.boolean_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_octet]:
                pass
                self.octet_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_any]:
                pass
                self.any_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_Object]:
                pass
                self.object_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_ValueBase]:
                pass
                self.value_base_type()
                self.addASTChild(currentAST, self.returnAST)
                base_type_spec_AST = currentAST.root
            else:
                synPredMatched139 = False
                if ((self.LA(1) >= LITERAL_float and self.LA(1) <= LITERAL_long)) and (_tokenSet_49.member(self.LA(2))) and (_tokenSet_50.member(self.LA(3))) and (_tokenSet_51.member(self.LA(4))):
                    _m139 = self.mark()
                    synPredMatched139 = True
                    self.inputState.guessing += 1
                    try:
                        pass
                        self.floating_pt_type()
                    except antlr.RecognitionException, pe:
                        synPredMatched139 = False
                    self.rewind(_m139)
                    self.inputState.guessing -= 1
                if synPredMatched139:
                    pass
                    self.floating_pt_type()
                    self.addASTChild(currentAST, self.returnAST)
                    base_type_spec_AST = currentAST.root
                elif ((self.LA(1) >= LITERAL_long and self.LA(1) <= LITERAL_unsigned)) and (_tokenSet_52.member(self.LA(2))) and (_tokenSet_53.member(self.LA(3))) and (_tokenSet_51.member(self.LA(4))):
                    pass
                    self.integer_type()
                    self.addASTChild(currentAST, self.returnAST)
                    base_type_spec_AST = currentAST.root
                else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = base_type_spec_AST
    
    def template_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        template_type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_sequence]:
                pass
                self.sequence_type()
                self.addASTChild(currentAST, self.returnAST)
                template_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_string]:
                pass
                self.string_type()
                self.addASTChild(currentAST, self.returnAST)
                template_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_wstring]:
                pass
                self.wide_string_type()
                self.addASTChild(currentAST, self.returnAST)
                template_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_fixed]:
                pass
                self.fixed_pt_type()
                self.addASTChild(currentAST, self.returnAST)
                template_type_spec_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_48)
            else:
                raise ex
        
        self.returnAST = template_type_spec_AST
    
    def any_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        any_type_AST = None
        try:      ## for error handling
            pass
            tmp134_AST = None
            tmp134_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp134_AST)
            self.match(LITERAL_any)
            any_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = any_type_AST
    
    def object_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        object_type_AST = None
        try:      ## for error handling
            pass
            tmp135_AST = None
            tmp135_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp135_AST)
            self.match(LITERAL_Object)
            object_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = object_type_AST
    
    def value_base_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        value_base_type_AST = None
        try:      ## for error handling
            pass
            tmp136_AST = None
            tmp136_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp136_AST)
            self.match(LITERAL_ValueBase)
            value_base_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_39)
            else:
                raise ex
        
        self.returnAST = value_base_type_AST
    
    def sequence_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        sequence_type_AST = None
        try:      ## for error handling
            pass
            tmp137_AST = None
            tmp137_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp137_AST)
            self.match(LITERAL_sequence)
            self.match(LT)
            self.simple_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.opt_pos_int()
            self.addASTChild(currentAST, self.returnAST)
            self.match(GT)
            sequence_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_48)
            else:
                raise ex
        
        self.returnAST = sequence_type_AST
    
    def fixed_pt_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        fixed_pt_type_AST = None
        try:      ## for error handling
            pass
            tmp140_AST = None
            tmp140_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp140_AST)
            self.match(LITERAL_fixed)
            self.match(LT)
            self.positive_int_const()
            self.addASTChild(currentAST, self.returnAST)
            self.match(COMMA)
            self.positive_int_const()
            self.addASTChild(currentAST, self.returnAST)
            self.match(GT)
            fixed_pt_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_48)
            else:
                raise ex
        
        self.returnAST = fixed_pt_type_AST
    
    def declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        declarator_AST = None
        try:      ## for error handling
            if (self.LA(1)==IDENT) and (self.LA(2)==SEMI or self.LA(2)==COMMA):
                pass
                self.simple_declarator()
                self.addASTChild(currentAST, self.returnAST)
                declarator_AST = currentAST.root
            elif (self.LA(1)==IDENT) and (self.LA(2)==LBRACK):
                pass
                self.complex_declarator()
                self.addASTChild(currentAST, self.returnAST)
                declarator_AST = currentAST.root
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_54)
            else:
                raise ex
        
        self.returnAST = declarator_AST
    
    def complex_declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        complex_declarator_AST = None
        try:      ## for error handling
            pass
            self.array_declarator()
            self.addASTChild(currentAST, self.returnAST)
            complex_declarator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_54)
            else:
                raise ex
        
        self.returnAST = complex_declarator_AST
    
    def array_declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        array_declarator_AST = None
        try:      ## for error handling
            pass
            tmp144_AST = None
            tmp144_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp144_AST)
            self.match(IDENT)
            _cnt193= 0
            while True:
                if (self.LA(1)==LBRACK):
                    pass
                    self.fixed_array_size()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
                _cnt193 += 1
            if _cnt193 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            array_declarator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_54)
            else:
                raise ex
        
        self.returnAST = array_declarator_AST
    
    def signed_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        signed_int_AST = None
        try:      ## for error handling
            if (self.LA(1)==LITERAL_short):
                pass
                self.signed_short_int()
                self.addASTChild(currentAST, self.returnAST)
                signed_int_AST = currentAST.root
            elif (self.LA(1)==LITERAL_long) and (_tokenSet_38.member(self.LA(2))):
                pass
                self.signed_long_int()
                self.addASTChild(currentAST, self.returnAST)
                signed_int_AST = currentAST.root
            elif (self.LA(1)==LITERAL_long) and (self.LA(2)==LITERAL_long):
                pass
                self.signed_longlong_int()
                self.addASTChild(currentAST, self.returnAST)
                signed_int_AST = currentAST.root
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = signed_int_AST
    
    def unsigned_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        unsigned_int_AST = None
        try:      ## for error handling
            if (self.LA(1)==LITERAL_unsigned) and (self.LA(2)==LITERAL_short):
                pass
                self.unsigned_short_int()
                self.addASTChild(currentAST, self.returnAST)
                unsigned_int_AST = currentAST.root
            elif (self.LA(1)==LITERAL_unsigned) and (self.LA(2)==LITERAL_long) and (_tokenSet_38.member(self.LA(3))):
                pass
                self.unsigned_long_int()
                self.addASTChild(currentAST, self.returnAST)
                unsigned_int_AST = currentAST.root
            elif (self.LA(1)==LITERAL_unsigned) and (self.LA(2)==LITERAL_long) and (self.LA(3)==LITERAL_long):
                pass
                self.unsigned_longlong_int()
                self.addASTChild(currentAST, self.returnAST)
                unsigned_int_AST = currentAST.root
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = unsigned_int_AST
    
    def signed_short_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        signed_short_int_AST = None
        try:      ## for error handling
            pass
            tmp145_AST = None
            tmp145_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp145_AST)
            self.match(LITERAL_short)
            signed_short_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = signed_short_int_AST
    
    def signed_long_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        signed_long_int_AST = None
        try:      ## for error handling
            pass
            tmp146_AST = None
            tmp146_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp146_AST)
            self.match(LITERAL_long)
            signed_long_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = signed_long_int_AST
    
    def signed_longlong_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        signed_longlong_int_AST = None
        try:      ## for error handling
            pass
            tmp147_AST = None
            tmp147_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp147_AST)
            self.match(LITERAL_long)
            tmp148_AST = None
            tmp148_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp148_AST)
            self.match(LITERAL_long)
            signed_longlong_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = signed_longlong_int_AST
    
    def unsigned_short_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        unsigned_short_int_AST = None
        try:      ## for error handling
            pass
            tmp149_AST = None
            tmp149_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp149_AST)
            self.match(LITERAL_unsigned)
            tmp150_AST = None
            tmp150_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp150_AST)
            self.match(LITERAL_short)
            unsigned_short_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = unsigned_short_int_AST
    
    def unsigned_long_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        unsigned_long_int_AST = None
        try:      ## for error handling
            pass
            tmp151_AST = None
            tmp151_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp151_AST)
            self.match(LITERAL_unsigned)
            tmp152_AST = None
            tmp152_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp152_AST)
            self.match(LITERAL_long)
            unsigned_long_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = unsigned_long_int_AST
    
    def unsigned_longlong_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        unsigned_longlong_int_AST = None
        try:      ## for error handling
            pass
            tmp153_AST = None
            tmp153_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp153_AST)
            self.match(LITERAL_unsigned)
            tmp154_AST = None
            tmp154_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp154_AST)
            self.match(LITERAL_long)
            tmp155_AST = None
            tmp155_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp155_AST)
            self.match(LITERAL_long)
            unsigned_longlong_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_38)
            else:
                raise ex
        
        self.returnAST = unsigned_longlong_int_AST
    
    def member_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        member_list_AST = None
        try:      ## for error handling
            pass
            _cnt167= 0
            while True:
                if (_tokenSet_13.member(self.LA(1))):
                    pass
                    self.member()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
                _cnt167 += 1
            if _cnt167 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            member_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = member_list_AST
    
    def member(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        member_AST = None
        try:      ## for error handling
            pass
            self.type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.declarators()
            self.addASTChild(currentAST, self.returnAST)
            self.match(SEMI)
            member_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_55)
            else:
                raise ex
        
        self.returnAST = member_AST
    
    def switch_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        switch_type_spec_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_long,LITERAL_short,LITERAL_unsigned]:
                pass
                self.integer_type()
                self.addASTChild(currentAST, self.returnAST)
                switch_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_char]:
                pass
                self.char_type()
                self.addASTChild(currentAST, self.returnAST)
                switch_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_boolean]:
                pass
                self.boolean_type()
                self.addASTChild(currentAST, self.returnAST)
                switch_type_spec_AST = currentAST.root
            elif la1 and la1 in [LITERAL_enum]:
                pass
                self.enum_type()
                self.addASTChild(currentAST, self.returnAST)
                switch_type_spec_AST = currentAST.root
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
                switch_type_spec_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_16)
            else:
                raise ex
        
        self.returnAST = switch_type_spec_AST
    
    def switch_body(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        switch_body_AST = None
        try:      ## for error handling
            pass
            self.case_stmt_list()
            self.addASTChild(currentAST, self.returnAST)
            switch_body_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = switch_body_AST
    
    def case_stmt_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        case_stmt_list_AST = None
        try:      ## for error handling
            pass
            _cnt174= 0
            while True:
                if (self.LA(1)==LITERAL_case or self.LA(1)==LITERAL_default):
                    pass
                    self.case_stmt()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
                _cnt174 += 1
            if _cnt174 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            case_stmt_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = case_stmt_list_AST
    
    def case_stmt(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        case_stmt_AST = None
        try:      ## for error handling
            pass
            _cnt177= 0
            while True:
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in [LITERAL_case]:
                    pass
                    tmp157_AST = None
                    tmp157_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp157_AST)
                    self.match(LITERAL_case)
                    self.const_exp()
                    self.addASTChild(currentAST, self.returnAST)
                    self.match(COLON)
                elif la1 and la1 in [LITERAL_default]:
                    pass
                    tmp159_AST = None
                    tmp159_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp159_AST)
                    self.match(LITERAL_default)
                    self.match(COLON)
                else:
                        break
                    
                _cnt177 += 1
            if _cnt177 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            self.element_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.match(SEMI)
            case_stmt_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_56)
            else:
                raise ex
        
        self.returnAST = case_stmt_AST
    
    def element_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        element_spec_AST = None
        try:      ## for error handling
            pass
            self.type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.declarator()
            self.addASTChild(currentAST, self.returnAST)
            element_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = element_spec_AST
    
    def enumerator_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        enumerator_list_AST = None
        try:      ## for error handling
            pass
            self.enumerator()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.enumerator()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            enumerator_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = enumerator_list_AST
    
    def enumerator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        enumerator_AST = None
        try:      ## for error handling
            pass
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            enumerator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_57)
            else:
                raise ex
        
        self.returnAST = enumerator_AST
    
    def opt_pos_int(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        opt_pos_int_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [COMMA]:
                pass
                self.match(COMMA)
                self.positive_int_const()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [GT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            opt_pos_int_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_58)
            else:
                raise ex
        
        self.returnAST = opt_pos_int_AST
    
    def fixed_array_size(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        fixed_array_size_AST = None
        try:      ## for error handling
            pass
            self.match(LBRACK)
            self.positive_int_const()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RBRACK)
            fixed_array_size_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_59)
            else:
                raise ex
        
        self.returnAST = fixed_array_size_AST
    
    def readonly_attr_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        readonly_attr_spec_AST = None
        try:      ## for error handling
            pass
            tmp166_AST = None
            tmp166_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp166_AST)
            self.match(LITERAL_readonly)
            tmp167_AST = None
            tmp167_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp167_AST)
            self.match(LITERAL_attribute)
            self.param_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.readonly_attr_declarator()
            self.addASTChild(currentAST, self.returnAST)
            readonly_attr_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = readonly_attr_spec_AST
    
    def attr_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        attr_spec_AST = None
        try:      ## for error handling
            pass
            tmp168_AST = None
            tmp168_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp168_AST)
            self.match(LITERAL_attribute)
            self.param_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.attr_declarator()
            self.addASTChild(currentAST, self.returnAST)
            attr_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = attr_spec_AST
    
    def opt_member_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        opt_member_list_AST = None
        try:      ## for error handling
            pass
            while True:
                if (_tokenSet_13.member(self.LA(1))):
                    pass
                    self.member()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            opt_member_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = opt_member_list_AST
    
    def op_attribute(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        op_attribute_AST = None
        try:      ## for error handling
            pass
            tmp169_AST = None
            tmp169_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp169_AST)
            self.match(LITERAL_oneway)
            op_attribute_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_33)
            else:
                raise ex
        
        self.returnAST = op_attribute_AST
    
    def op_type_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        op_type_spec_AST = None
        try:      ## for error handling
            pass
            self.param_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [STAR]:
                pass
                self.allow_indirection()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [IDENT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            op_type_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_37)
            else:
                raise ex
        
        self.returnAST = op_type_spec_AST
    
    def parameter_dcls(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        parameter_dcls_AST = None
        try:      ## for error handling
            pass
            self.match(LPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LBRACK,LITERAL_in,LITERAL_out,LITERAL_inout]:
                pass
                self.param_dcl_list()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [RPAREN]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(RPAREN)
            parameter_dcls_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_60)
            else:
                raise ex
        
        self.returnAST = parameter_dcls_AST
    
    def context_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        context_expr_AST = None
        try:      ## for error handling
            pass
            tmp172_AST = None
            tmp172_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp172_AST)
            self.match(LITERAL_context)
            self.match(LPAREN)
            self.string_literal_list()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RPAREN)
            context_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = context_expr_AST
    
    def allow_indirection(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        allow_indirection_AST = None
        try:      ## for error handling
            pass
            _cnt217= 0
            while True:
                if (self.LA(1)==STAR):
                    pass
                    tmp175_AST = None
                    tmp175_AST = self.astFactory.create(self.LT(1))
                    self.addASTChild(currentAST, tmp175_AST)
                    self.match(STAR)
                else:
                    break
                
                _cnt217 += 1
            if _cnt217 < 1:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            allow_indirection_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_37)
            else:
                raise ex
        
        self.returnAST = allow_indirection_AST
    
    def param_dcl_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        param_dcl_list_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LBRACK]:
                pass
                self.decorator()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_in,LITERAL_out,LITERAL_inout]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.param_dcl()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LBRACK]:
                        pass
                        self.decorator()
                        self.addASTChild(currentAST, self.returnAST)
                    elif la1 and la1 in [LITERAL_in,LITERAL_out,LITERAL_inout]:
                        pass
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                    self.param_dcl()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            param_dcl_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_16)
            else:
                raise ex
        
        self.returnAST = param_dcl_list_AST
    
    def param_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        param_dcl_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_in]:
                pass
                tmp177_AST = None
                tmp177_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp177_AST)
                self.match(LITERAL_in)
            elif la1 and la1 in [LITERAL_out]:
                pass
                tmp178_AST = None
                tmp178_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp178_AST)
                self.match(LITERAL_out)
            elif la1 and la1 in [LITERAL_inout]:
                pass
                tmp179_AST = None
                tmp179_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp179_AST)
                self.match(LITERAL_inout)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.param_type_spec()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [STAR]:
                pass
                self.allow_indirection()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [IDENT]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.simple_declarator()
            self.addASTChild(currentAST, self.returnAST)
            param_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_32)
            else:
                raise ex
        
        self.returnAST = param_dcl_AST
    
    def string_literal_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        string_literal_list_AST = None
        try:      ## for error handling
            pass
            self.string_literal()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.string_literal()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            string_literal_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_16)
            else:
                raise ex
        
        self.returnAST = string_literal_list_AST
    
    def imported_scope(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        imported_scope_AST = None
        try:      ## for error handling
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
                imported_scope_AST = currentAST.root
            elif la1 and la1 in [STRING_LITERAL]:
                pass
                self.string_literal()
                self.addASTChild(currentAST, self.returnAST)
                imported_scope_AST = currentAST.root
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = imported_scope_AST
    
    def readonly_attr_declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        readonly_attr_declarator_AST = None
        try:      ## for error handling
            pass
            self.simple_declarator()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_raises]:
                pass
                self.raises_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI,COMMA]:
                pass
                while True:
                    if (self.LA(1)==COMMA):
                        pass
                        self.match(COMMA)
                        self.simple_declarator()
                        self.addASTChild(currentAST, self.returnAST)
                    else:
                        break
                    
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            readonly_attr_declarator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = readonly_attr_declarator_AST
    
    def attr_declarator(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        attr_declarator_AST = None
        try:      ## for error handling
            pass
            self.simple_declarator()
            self.addASTChild(currentAST, self.returnAST)
            synPredMatched244 = False
            if (self.LA(1)==SEMI or self.LA(1)==LITERAL_getraises or self.LA(1)==LITERAL_setraises) and (_tokenSet_61.member(self.LA(2))) and (_tokenSet_62.member(self.LA(3))) and (_tokenSet_63.member(self.LA(4))):
                _m244 = self.mark()
                synPredMatched244 = True
                self.inputState.guessing += 1
                try:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in [LITERAL_getraises]:
                        pass
                        self.match(LITERAL_getraises)
                    elif la1 and la1 in [LITERAL_setraises]:
                        pass
                        self.match(LITERAL_setraises)
                    else:
                            raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                        
                except antlr.RecognitionException, pe:
                    synPredMatched244 = False
                self.rewind(_m244)
                self.inputState.guessing -= 1
            if synPredMatched244:
                pass
                self.attr_raises_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif (self.LA(1)==SEMI or self.LA(1)==COMMA) and (_tokenSet_64.member(self.LA(2))) and (_tokenSet_65.member(self.LA(3))) and (_tokenSet_66.member(self.LA(4))):
                pass
                while True:
                    if (self.LA(1)==COMMA):
                        pass
                        self.match(COMMA)
                        self.simple_declarator()
                        self.addASTChild(currentAST, self.returnAST)
                    else:
                        break
                    
            else:
                raise antlr.NoViableAltException(self.LT(1), self.getFilename())
            
            attr_declarator_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = attr_declarator_AST
    
    def attr_raises_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        attr_raises_expr_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_getraises]:
                pass
                self.get_excep_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI,LITERAL_setraises]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_setraises]:
                pass
                self.set_excep_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            attr_raises_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = attr_raises_expr_AST
    
    def get_excep_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        get_excep_expr_AST = None
        try:      ## for error handling
            pass
            tmp183_AST = None
            tmp183_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp183_AST)
            self.match(LITERAL_getraises)
            self.exception_list()
            self.addASTChild(currentAST, self.returnAST)
            get_excep_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_67)
            else:
                raise ex
        
        self.returnAST = get_excep_expr_AST
    
    def set_excep_expr(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        set_excep_expr_AST = None
        try:      ## for error handling
            pass
            tmp184_AST = None
            tmp184_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp184_AST)
            self.match(LITERAL_setraises)
            self.exception_list()
            self.addASTChild(currentAST, self.returnAST)
            set_excep_expr_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = set_excep_expr_AST
    
    def exception_list(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        exception_list_AST = None
        try:      ## for error handling
            pass
            self.match(LPAREN)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.scoped_name()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RPAREN)
            exception_list_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_67)
            else:
                raise ex
        
        self.returnAST = exception_list_AST
    
    def component_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        component_dcl_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [COLON]:
                pass
                self.component_inheritance_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LCURLY,LITERAL_supports]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_supports]:
                pass
                self.supported_interface_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(LCURLY)
            self.component_body()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RCURLY)
            component_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = component_dcl_AST
    
    def component_inheritance_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        component_inheritance_spec_AST = None
        try:      ## for error handling
            pass
            tmp190_AST = None
            tmp190_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp190_AST)
            self.match(COLON)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            component_inheritance_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_29)
            else:
                raise ex
        
        self.returnAST = component_inheritance_spec_AST
    
    def supported_interface_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        supported_interface_spec_AST = None
        try:      ## for error handling
            pass
            tmp191_AST = None
            tmp191_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp191_AST)
            self.match(LITERAL_supports)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            while True:
                if (self.LA(1)==COMMA):
                    pass
                    self.match(COMMA)
                    self.scoped_name()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            supported_interface_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_68)
            else:
                raise ex
        
        self.returnAST = supported_interface_spec_AST
    
    def component_body(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        component_body_AST = None
        try:      ## for error handling
            pass
            while True:
                if (_tokenSet_69.member(self.LA(1))):
                    pass
                    self.component_export()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            component_body_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_19)
            else:
                raise ex
        
        self.returnAST = component_body_AST
    
    def component_export(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        component_export_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_provides]:
                pass
                self.provides_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_uses]:
                pass
                self.uses_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_emits]:
                pass
                self.emits_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_publishes]:
                pass
                self.publishes_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_consumes]:
                pass
                self.consumes_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_readonly,LITERAL_attribute]:
                pass
                self.attr_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            component_export_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_70)
            else:
                raise ex
        
        self.returnAST = component_export_AST
    
    def provides_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        provides_dcl_AST = None
        try:      ## for error handling
            pass
            tmp199_AST = None
            tmp199_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp199_AST)
            self.match(LITERAL_provides)
            self.interface_type()
            self.addASTChild(currentAST, self.returnAST)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            provides_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = provides_dcl_AST
    
    def uses_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        uses_dcl_AST = None
        try:      ## for error handling
            pass
            tmp200_AST = None
            tmp200_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp200_AST)
            self.match(LITERAL_uses)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_multiple]:
                pass
                tmp201_AST = None
                tmp201_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp201_AST)
                self.match(LITERAL_multiple)
            elif la1 and la1 in [SCOPEOP,IDENT,LITERAL_Object]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.interface_type()
            self.addASTChild(currentAST, self.returnAST)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            uses_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = uses_dcl_AST
    
    def emits_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        emits_dcl_AST = None
        try:      ## for error handling
            pass
            tmp202_AST = None
            tmp202_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp202_AST)
            self.match(LITERAL_emits)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            emits_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = emits_dcl_AST
    
    def publishes_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        publishes_dcl_AST = None
        try:      ## for error handling
            pass
            tmp203_AST = None
            tmp203_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp203_AST)
            self.match(LITERAL_publishes)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            publishes_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = publishes_dcl_AST
    
    def consumes_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        consumes_dcl_AST = None
        try:      ## for error handling
            pass
            tmp204_AST = None
            tmp204_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp204_AST)
            self.match(LITERAL_consumes)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            consumes_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = consumes_dcl_AST
    
    def interface_type(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        interface_type_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [SCOPEOP,IDENT]:
                pass
                self.scoped_name()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_Object]:
                pass
                tmp205_AST = None
                tmp205_AST = self.astFactory.create(self.LT(1))
                self.addASTChild(currentAST, tmp205_AST)
                self.match(LITERAL_Object)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            interface_type_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_37)
            else:
                raise ex
        
        self.returnAST = interface_type_AST
    
    def home_header(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        home_header_AST = None
        try:      ## for error handling
            pass
            tmp206_AST = None
            tmp206_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp206_AST)
            self.match(LITERAL_home)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [COLON]:
                pass
                self.home_inheritance_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_supports,LITERAL_manages]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_supports]:
                pass
                self.supported_interface_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_manages]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            self.match(LITERAL_manages)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_primarykey]:
                pass
                self.primary_key_spec()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LCURLY]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            home_header_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = home_header_AST
    
    def home_body(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        home_body_AST = None
        try:      ## for error handling
            pass
            self.match(LCURLY)
            while True:
                if (_tokenSet_71.member(self.LA(1))):
                    pass
                    self.home_export()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RCURLY)
            home_body_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = home_body_AST
    
    def home_inheritance_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        home_inheritance_spec_AST = None
        try:      ## for error handling
            pass
            tmp210_AST = None
            tmp210_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp210_AST)
            self.match(COLON)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            home_inheritance_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_72)
            else:
                raise ex
        
        self.returnAST = home_inheritance_spec_AST
    
    def primary_key_spec(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        primary_key_spec_AST = None
        try:      ## for error handling
            pass
            tmp211_AST = None
            tmp211_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp211_AST)
            self.match(LITERAL_primarykey)
            self.scoped_name()
            self.addASTChild(currentAST, self.returnAST)
            primary_key_spec_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_20)
            else:
                raise ex
        
        self.returnAST = primary_key_spec_AST
    
    def home_export(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        home_export_AST = None
        try:      ## for error handling
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LBRACK,SCOPEOP,IDENT,LITERAL_const,LITERAL_typedef,LITERAL_native,LITERAL_float,LITERAL_double,LITERAL_long,LITERAL_short,LITERAL_unsigned,LITERAL_char,LITERAL_wchar,LITERAL_boolean,LITERAL_octet,LITERAL_any,LITERAL_Object,LITERAL_struct,LITERAL_union,LITERAL_enum,LITERAL_string,LITERAL_wstring,LITERAL_exception,LITERAL_oneway,LITERAL_ValueBase,LITERAL_typeid,LITERAL_typeprefix,LITERAL_readonly,LITERAL_attribute]:
                pass
                self.export()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [LITERAL_factory]:
                pass
                self.factory_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            elif la1 and la1 in [LITERAL_finder]:
                pass
                self.finder_dcl()
                self.addASTChild(currentAST, self.returnAST)
                self.match(SEMI)
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            home_export_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_73)
            else:
                raise ex
        
        self.returnAST = home_export_AST
    
    def factory_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        factory_dcl_AST = None
        try:      ## for error handling
            pass
            tmp214_AST = None
            tmp214_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp214_AST)
            self.match(LITERAL_factory)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LPAREN)
            self.init_param_decls()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_raises]:
                pass
                self.raises_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            factory_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = factory_dcl_AST
    
    def finder_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        finder_dcl_AST = None
        try:      ## for error handling
            pass
            tmp217_AST = None
            tmp217_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp217_AST)
            self.match(LITERAL_finder)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LPAREN)
            self.init_param_decls()
            self.addASTChild(currentAST, self.returnAST)
            self.match(RPAREN)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LITERAL_raises]:
                pass
                self.raises_expr()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            finder_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = finder_dcl_AST
    
    def event_abs(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_abs_AST = None
        try:      ## for error handling
            pass
            tmp220_AST = None
            tmp220_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp220_AST)
            self.match(LITERAL_abstract)
            self.event_header()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY,COLON,LITERAL_supports]:
                pass
                self.event_abs_dcl()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            event_abs_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = event_abs_AST
    
    def event_custom(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_custom_AST = None
        try:      ## for error handling
            pass
            tmp221_AST = None
            tmp221_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp221_AST)
            self.match(LITERAL_custom)
            self.event_header()
            self.addASTChild(currentAST, self.returnAST)
            self.event_elem_dcl()
            self.addASTChild(currentAST, self.returnAST)
            event_custom_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = event_custom_AST
    
    def event_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_dcl_AST = None
        try:      ## for error handling
            pass
            self.event_header()
            self.addASTChild(currentAST, self.returnAST)
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in [LCURLY,COLON,LITERAL_supports]:
                pass
                self.event_elem_dcl()
                self.addASTChild(currentAST, self.returnAST)
            elif la1 and la1 in [SEMI]:
                pass
            else:
                    raise antlr.NoViableAltException(self.LT(1), self.getFilename())
                
            event_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = event_dcl_AST
    
    def event_header(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_header_AST = None
        try:      ## for error handling
            pass
            tmp222_AST = None
            tmp222_AST = self.astFactory.create(self.LT(1))
            self.addASTChild(currentAST, tmp222_AST)
            self.match(LITERAL_eventtype)
            self.identifier()
            self.addASTChild(currentAST, self.returnAST)
            event_header_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_74)
            else:
                raise ex
        
        self.returnAST = event_header_AST
    
    def event_abs_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_abs_dcl_AST = None
        try:      ## for error handling
            pass
            self.value_inheritance_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            while True:
                if (_tokenSet_21.member(self.LA(1))):
                    pass
                    self.export()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RCURLY)
            event_abs_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = event_abs_dcl_AST
    
    def event_elem_dcl(self):    
        
        self.returnAST = None
        currentAST = antlr.ASTPair()
        event_elem_dcl_AST = None
        try:      ## for error handling
            pass
            self.value_inheritance_spec()
            self.addASTChild(currentAST, self.returnAST)
            self.match(LCURLY)
            while True:
                if (_tokenSet_21.member(self.LA(1))):
                    pass
                    self.export()
                    self.addASTChild(currentAST, self.returnAST)
                else:
                    break
                
            self.match(RCURLY)
            event_elem_dcl_AST = currentAST.root
        
        except antlr.RecognitionException, ex:
            if not self.inputState.guessing:
                self.reportError(ex)
                self.consume()
                self.consumeUntil(_tokenSet_12)
            else:
                raise ex
        
        self.returnAST = event_elem_dcl_AST
    
    
    def buildTokenTypeASTClassMap(self):
        self.tokenTypeToASTClassMap = None

_tokenNames = [
    "<0>", 
    "EOF", 
    "<2>", 
    "NULL_TREE_LOOKAHEAD", 
    ";", 
    "\"abstract\"", 
    "\"local\"", 
    "\"interface\"", 
    "\"custom\"", 
    "\"valuetype\"", 
    "\"eventtype\"", 
    "[", 
    ",", 
    "]", 
    "(", 
    ")", 
    "\"module\"", 
    "{", 
    "}", 
    ":", 
    "::", 
    "an identifer", 
    "\"truncatable\"", 
    "\"supports\"", 
    "\"public\"", 
    "\"private\"", 
    "\"factory\"", 
    "\"in\"", 
    "\"const\"", 
    "=", 
    "|", 
    "^", 
    "&", 
    "<<", 
    ">>", 
    "+", 
    "-", 
    "*", 
    "/", 
    "%", 
    "~", 
    "\"TRUE\"", 
    "\"FALSE\"", 
    "\"typedef\"", 
    "\"native\"", 
    "\"float\"", 
    "\"double\"", 
    "\"long\"", 
    "\"short\"", 
    "\"unsigned\"", 
    "\"char\"", 
    "\"wchar\"", 
    "\"boolean\"", 
    "\"octet\"", 
    "\"any\"", 
    "\"Object\"", 
    "\"struct\"", 
    "\"union\"", 
    "\"switch\"", 
    "\"case\"", 
    "\"default\"", 
    "\"enum\"", 
    "\"sequence\"", 
    "<", 
    ">", 
    "\"string\"", 
    "\"wstring\"", 
    "\"exception\"", 
    "\"oneway\"", 
    "\"out\"", 
    "\"inout\"", 
    "\"raises\"", 
    "\"context\"", 
    "\"fixed\"", 
    "\"ValueBase\"", 
    "\"import\"", 
    "\"typeid\"", 
    "\"typeprefix\"", 
    "\"readonly\"", 
    "\"attribute\"", 
    "\"getraises\"", 
    "\"setraises\"", 
    "\"component\"", 
    "\"provides\"", 
    "\"uses\"", 
    "\"multiple\"", 
    "\"emits\"", 
    "\"publishes\"", 
    "\"consumes\"", 
    "\"home\"", 
    "\"manages\"", 
    "\"primarykey\"", 
    "\"finder\"", 
    "an integer value", 
    "an octal value", 
    "a hexadecimal value value", 
    "a string literal", 
    "a wide string literal", 
    "a character literal", 
    "a wide character literal", 
    "FIXED", 
    "a floating point value", 
    "?", 
    ".", 
    "!", 
    "_", 
    "white space", 
    "a preprocessor directive", 
    "a comment", 
    "a comment", 
    "an escape sequence", 
    "an escaped character value", 
    "a digit", 
    "a non-zero digit", 
    "an octal digit", 
    "a hexadecimal digit", 
    "an escaped identifer"
]
    

### generate bit set
def mk_tokenSet_0(): 
    ### var1
    data = [ 2522042179875049440L, 33828872L, 0L, 0L]
    return data
_tokenSet_0 = antlr.BitSet(mk_tokenSet_0())

### generate bit set
def mk_tokenSet_1(): 
    ### var1
    data = [ 2L, 0L]
    return data
_tokenSet_1 = antlr.BitSet(mk_tokenSet_1())

### generate bit set
def mk_tokenSet_2(): 
    ### var1
    data = [ 2522042179875049440L, 33830920L, 0L, 0L]
    return data
_tokenSet_2 = antlr.BitSet(mk_tokenSet_2())

### generate bit set
def mk_tokenSet_3(): 
    ### var1
    data = [ 2522042179875049442L, 33828872L, 0L, 0L]
    return data
_tokenSet_3 = antlr.BitSet(mk_tokenSet_3())

### generate bit set
def mk_tokenSet_4(): 
    ### var1
    data = [ 2594064589678252000L, 33830014L, 0L, 0L]
    return data
_tokenSet_4 = antlr.BitSet(mk_tokenSet_4())

### generate bit set
def mk_tokenSet_5(): 
    ### var1
    data = [ 2752528L, 0L]
    return data
_tokenSet_5 = antlr.BitSet(mk_tokenSet_5())

### generate bit set
def mk_tokenSet_6(): 
    ### var1
    data = [ 2594064589544951794L, 33879070L, 0L, 0L]
    return data
_tokenSet_6 = antlr.BitSet(mk_tokenSet_6())

### generate bit set
def mk_tokenSet_7(): 
    ### var1
    data = [ 7205724219432894480L, 1542L, 0L, 0L]
    return data
_tokenSet_7 = antlr.BitSet(mk_tokenSet_7())

### generate bit set
def mk_tokenSet_8(): 
    ### var1
    data = [ -6629307447179800590L, 33879070L, 0L, 0L]
    return data
_tokenSet_8 = antlr.BitSet(mk_tokenSet_8())

### generate bit set
def mk_tokenSet_9(): 
    ### var1
    data = [ 11141136L, 0L]
    return data
_tokenSet_9 = antlr.BitSet(mk_tokenSet_9())

### generate bit set
def mk_tokenSet_10(): 
    ### var1
    data = [ 2594064589557534706L, 33879070L, 0L, 0L]
    return data
_tokenSet_10 = antlr.BitSet(mk_tokenSet_10())

### generate bit set
def mk_tokenSet_11(): 
    ### var1
    data = [ 2522042179875311586L, 33828872L, 0L, 0L]
    return data
_tokenSet_11 = antlr.BitSet(mk_tokenSet_11())

### generate bit set
def mk_tokenSet_12(): 
    ### var1
    data = [ 16L, 0L]
    return data
_tokenSet_12 = antlr.BitSet(mk_tokenSet_12())

### generate bit set
def mk_tokenSet_13(): 
    ### var1
    data = [ 7205724219423850496L, 1542L, 0L, 0L]
    return data
_tokenSet_13 = antlr.BitSet(mk_tokenSet_13())

### generate bit set
def mk_tokenSet_14(): 
    ### var1
    data = [ 12288L, 0L]
    return data
_tokenSet_14 = antlr.BitSet(mk_tokenSet_14())

### generate bit set
def mk_tokenSet_15(): 
    ### var1
    data = [ 7493955694559686672L, 4496492167L, 0L, 0L]
    return data
_tokenSet_15 = antlr.BitSet(mk_tokenSet_15())

### generate bit set
def mk_tokenSet_16(): 
    ### var1
    data = [ 32768L, 0L]
    return data
_tokenSet_16 = antlr.BitSet(mk_tokenSet_16())

### generate bit set
def mk_tokenSet_17(): 
    ### var1
    data = [ 569360L, 1L, 0L, 0L]
    return data
_tokenSet_17 = antlr.BitSet(mk_tokenSet_17())

### generate bit set
def mk_tokenSet_18(): 
    ### var1
    data = [ 2522042179875047392L, 33828872L, 0L, 0L]
    return data
_tokenSet_18 = antlr.BitSet(mk_tokenSet_18())

### generate bit set
def mk_tokenSet_19(): 
    ### var1
    data = [ 262144L, 0L]
    return data
_tokenSet_19 = antlr.BitSet(mk_tokenSet_19())

### generate bit set
def mk_tokenSet_20(): 
    ### var1
    data = [ 131072L, 0L]
    return data
_tokenSet_20 = antlr.BitSet(mk_tokenSet_20())

### generate bit set
def mk_tokenSet_21(): 
    ### var1
    data = [ 2594064589543966720L, 62494L, 0L, 0L]
    return data
_tokenSet_21 = antlr.BitSet(mk_tokenSet_21())

### generate bit set
def mk_tokenSet_22(): 
    ### var1
    data = [ 2594064589661669376L, 268497950L, 0L, 0L]
    return data
_tokenSet_22 = antlr.BitSet(mk_tokenSet_22())

### generate bit set
def mk_tokenSet_23(): 
    ### var1
    data = [ 163840L, 0L]
    return data
_tokenSet_23 = antlr.BitSet(mk_tokenSet_23())

### generate bit set
def mk_tokenSet_24(): 
    ### var1
    data = [ 135168L, 0L]
    return data
_tokenSet_24 = antlr.BitSet(mk_tokenSet_24())

### generate bit set
def mk_tokenSet_25(): 
    ### var1
    data = [ 1098449072144L, 4496293889L, 0L, 0L]
    return data
_tokenSet_25 = antlr.BitSet(mk_tokenSet_25())

### generate bit set
def mk_tokenSet_26(): 
    ### var1
    data = [ 2594064589661407232L, 62494L, 0L, 0L]
    return data
_tokenSet_26 = antlr.BitSet(mk_tokenSet_26())

### generate bit set
def mk_tokenSet_27(): 
    ### var1
    data = [ 2097168L, 0L]
    return data
_tokenSet_27 = antlr.BitSet(mk_tokenSet_27())

### generate bit set
def mk_tokenSet_28(): 
    ### var1
    data = [ 2594064589661669376L, 62494L, 0L, 0L]
    return data
_tokenSet_28 = antlr.BitSet(mk_tokenSet_28())

### generate bit set
def mk_tokenSet_29(): 
    ### var1
    data = [ 8519680L, 0L]
    return data
_tokenSet_29 = antlr.BitSet(mk_tokenSet_29())

### generate bit set
def mk_tokenSet_30(): 
    ### var1
    data = [ 8523776L, 0L]
    return data
_tokenSet_30 = antlr.BitSet(mk_tokenSet_30())

### generate bit set
def mk_tokenSet_31(): 
    ### var1
    data = [ 16L, 256L, 0L, 0L]
    return data
_tokenSet_31 = antlr.BitSet(mk_tokenSet_31())

### generate bit set
def mk_tokenSet_32(): 
    ### var1
    data = [ 36864L, 0L]
    return data
_tokenSet_32 = antlr.BitSet(mk_tokenSet_32())

### generate bit set
def mk_tokenSet_33(): 
    ### var1
    data = [ 72022409668984832L, 1030L, 0L, 0L]
    return data
_tokenSet_33 = antlr.BitSet(mk_tokenSet_33())

### generate bit set
def mk_tokenSet_34(): 
    ### var1
    data = [ 137441050624L, 0L]
    return data
_tokenSet_34 = antlr.BitSet(mk_tokenSet_34())

### generate bit set
def mk_tokenSet_35(): 
    ### var1
    data = [ 36880L, 196736L, 0L, 0L]
    return data
_tokenSet_35 = antlr.BitSet(mk_tokenSet_35())

### generate bit set
def mk_tokenSet_36(): 
    ### var1
    data = [ 7800200642560L, 274341036032L, 0L, 0L]
    return data
_tokenSet_36 = antlr.BitSet(mk_tokenSet_36())

### generate bit set
def mk_tokenSet_37(): 
    ### var1
    data = [ 2097152L, 0L]
    return data
_tokenSet_37 = antlr.BitSet(mk_tokenSet_37())

### generate bit set
def mk_tokenSet_38(): 
    ### var1
    data = [ 137441087504L, 1L, 0L, 0L]
    return data
_tokenSet_38 = antlr.BitSet(mk_tokenSet_38())

### generate bit set
def mk_tokenSet_39(): 
    ### var1
    data = [ 137441054736L, 1L, 0L, 0L]
    return data
_tokenSet_39 = antlr.BitSet(mk_tokenSet_39())

### generate bit set
def mk_tokenSet_40(): 
    ### var1
    data = [ 1074311184L, 1L, 0L, 0L]
    return data
_tokenSet_40 = antlr.BitSet(mk_tokenSet_40())

### generate bit set
def mk_tokenSet_41(): 
    ### var1
    data = [ 3221794832L, 1L, 0L, 0L]
    return data
_tokenSet_41 = antlr.BitSet(mk_tokenSet_41())

### generate bit set
def mk_tokenSet_42(): 
    ### var1
    data = [ 7516762128L, 1L, 0L, 0L]
    return data
_tokenSet_42 = antlr.BitSet(mk_tokenSet_42())

### generate bit set
def mk_tokenSet_43(): 
    ### var1
    data = [ 33286565904L, 1L, 0L, 0L]
    return data
_tokenSet_43 = antlr.BitSet(mk_tokenSet_43())

### generate bit set
def mk_tokenSet_44(): 
    ### var1
    data = [ 136365781008L, 1L, 0L, 0L]
    return data
_tokenSet_44 = antlr.BitSet(mk_tokenSet_44())

### generate bit set
def mk_tokenSet_45(): 
    ### var1
    data = [ 1098438455312L, 1L, 0L, 0L]
    return data
_tokenSet_45 = antlr.BitSet(mk_tokenSet_45())

### generate bit set
def mk_tokenSet_46(): 
    ### var1
    data = [ 12288L, 1L, 0L, 0L]
    return data
_tokenSet_46 = antlr.BitSet(mk_tokenSet_46())

### generate bit set
def mk_tokenSet_47(): 
    ### var1
    data = [ 2129936L, 0L]
    return data
_tokenSet_47 = antlr.BitSet(mk_tokenSet_47())

### generate bit set
def mk_tokenSet_48(): 
    ### var1
    data = [ 2101264L, 1L, 0L, 0L]
    return data
_tokenSet_48 = antlr.BitSet(mk_tokenSet_48())

### generate bit set
def mk_tokenSet_49(): 
    ### var1
    data = [ 70506185232400L, 1L, 0L, 0L]
    return data
_tokenSet_49 = antlr.BitSet(mk_tokenSet_49())

### generate bit set
def mk_tokenSet_50(): 
    ### var1
    data = [ 2522050116978073586L, 274375061641L, 0L, 0L]
    return data
_tokenSet_50 = antlr.BitSet(mk_tokenSet_50())

### generate bit set
def mk_tokenSet_51(): 
    ### var1
    data = [ 8935141660152946674L, 274674481151L, 0L, 0L]
    return data
_tokenSet_51 = antlr.BitSet(mk_tokenSet_51())

### generate bit set
def mk_tokenSet_52(): 
    ### var1
    data = [ 422349906120720L, 1L, 0L, 0L]
    return data
_tokenSet_52 = antlr.BitSet(mk_tokenSet_52())

### generate bit set
def mk_tokenSet_53(): 
    ### var1
    data = [ 2522190854466428914L, 274375061641L, 0L, 0L]
    return data
_tokenSet_53 = antlr.BitSet(mk_tokenSet_53())

### generate bit set
def mk_tokenSet_54(): 
    ### var1
    data = [ 4112L, 0L]
    return data
_tokenSet_54 = antlr.BitSet(mk_tokenSet_54())

### generate bit set
def mk_tokenSet_55(): 
    ### var1
    data = [ 7205724219424112640L, 1542L, 0L, 0L]
    return data
_tokenSet_55 = antlr.BitSet(mk_tokenSet_55())

### generate bit set
def mk_tokenSet_56(): 
    ### var1
    data = [ 1729382256910532608L, 0L]
    return data
_tokenSet_56 = antlr.BitSet(mk_tokenSet_56())

### generate bit set
def mk_tokenSet_57(): 
    ### var1
    data = [ 266240L, 0L]
    return data
_tokenSet_57 = antlr.BitSet(mk_tokenSet_57())

### generate bit set
def mk_tokenSet_58(): 
    ### var1
    data = [ 0L, 1L, 0L, 0L]
    return data
_tokenSet_58 = antlr.BitSet(mk_tokenSet_58())

### generate bit set
def mk_tokenSet_59(): 
    ### var1
    data = [ 6160L, 0L]
    return data
_tokenSet_59 = antlr.BitSet(mk_tokenSet_59())

### generate bit set
def mk_tokenSet_60(): 
    ### var1
    data = [ 16L, 384L, 0L, 0L]
    return data
_tokenSet_60 = antlr.BitSet(mk_tokenSet_60())

### generate bit set
def mk_tokenSet_61(): 
    ### var1
    data = [ 2594064589661685760L, 299430942L, 0L, 0L]
    return data
_tokenSet_61 = antlr.BitSet(mk_tokenSet_61())

### generate bit set
def mk_tokenSet_62(): 
    ### var1
    data = [ -2017647679991971824L, 2131462L, 0L, 0L]
    return data
_tokenSet_62 = antlr.BitSet(mk_tokenSet_62())

### generate bit set
def mk_tokenSet_63(): 
    ### var1
    data = [ -6341069134059012110L, 274374865934L, 0L, 0L]
    return data
_tokenSet_63 = antlr.BitSet(mk_tokenSet_63())

### generate bit set
def mk_tokenSet_64(): 
    ### var1
    data = [ 2594064589661669376L, 299430942L, 0L, 0L]
    return data
_tokenSet_64 = antlr.BitSet(mk_tokenSet_64())

### generate bit set
def mk_tokenSet_65(): 
    ### var1
    data = [ -2017647679991967728L, 2131462L, 0L, 0L]
    return data
_tokenSet_65 = antlr.BitSet(mk_tokenSet_65())

### generate bit set
def mk_tokenSet_66(): 
    ### var1
    data = [ -6341069133941604366L, 274674283550L, 0L, 0L]
    return data
_tokenSet_66 = antlr.BitSet(mk_tokenSet_66())

### generate bit set
def mk_tokenSet_67(): 
    ### var1
    data = [ 16L, 131072L, 0L, 0L]
    return data
_tokenSet_67 = antlr.BitSet(mk_tokenSet_67())

### generate bit set
def mk_tokenSet_68(): 
    ### var1
    data = [ 131072L, 67108864L, 0L, 0L]
    return data
_tokenSet_68 = antlr.BitSet(mk_tokenSet_68())

### generate bit set
def mk_tokenSet_69(): 
    ### var1
    data = [ 0L, 30982144L, 0L, 0L]
    return data
_tokenSet_69 = antlr.BitSet(mk_tokenSet_69())

### generate bit set
def mk_tokenSet_70(): 
    ### var1
    data = [ 262144L, 30982144L, 0L, 0L]
    return data
_tokenSet_70 = antlr.BitSet(mk_tokenSet_70())

### generate bit set
def mk_tokenSet_71(): 
    ### var1
    data = [ 2594064589611075584L, 268497950L, 0L, 0L]
    return data
_tokenSet_71 = antlr.BitSet(mk_tokenSet_71())

### generate bit set
def mk_tokenSet_72(): 
    ### var1
    data = [ 8388608L, 67108864L, 0L, 0L]
    return data
_tokenSet_72 = antlr.BitSet(mk_tokenSet_72())

### generate bit set
def mk_tokenSet_73(): 
    ### var1
    data = [ 2594064589611337728L, 268497950L, 0L, 0L]
    return data
_tokenSet_73 = antlr.BitSet(mk_tokenSet_73())

### generate bit set
def mk_tokenSet_74(): 
    ### var1
    data = [ 9043984L, 0L]
    return data
_tokenSet_74 = antlr.BitSet(mk_tokenSet_74())
    
