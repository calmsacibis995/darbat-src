### $ANTLR 2.7.5 (20050403): "CPP_parser.g" -> "CPPLexer.py"$
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
### preamble action >>> 

### preamble action <<< 
### >>>The Literals<<<
literals = {}
literals[u"namespace"] = 13
literals[u"public"] = 64
literals[u"_cdecl"] = 131
literals[u"__stdcall"] = 26
literals[u"extern"] = 17
literals[u"case"] = 75
literals[u"delete"] = 141
literals[u"new"] = 130
literals[u"__declspec"] = 54
literals[u"__w64"] = 46
literals[u"_declspec"] = 53
literals[u"_near"] = 133
literals[u"__int64"] = 45
literals[u"inline"] = 12
literals[u"unsigned"] = 49
literals[u"static_cast"] = 127
literals[u"return"] = 86
literals[u"mutable"] = 36
literals[u"sizeof"] = 123
literals[u"protected"] = 65
literals[u"false"] = 61
literals[u"default"] = 76
literals[u"do"] = 81
literals[u"__interrupt"] = 137
literals[u"_far"] = 135
literals[u"_inline"] = 20
literals[u"_int64"] = 44
literals[u"union"] = 57
literals[u"catch"] = 88
literals[u"volatile"] = 38
literals[u"explicit"] = 23
literals[u"_asm"] = 90
literals[u"__asm__"] = 92
literals[u"if"] = 77
literals[u"double"] = 51
literals[u"const_cast"] = 37
literals[u"typedef"] = 7
literals[u"pascal"] = 138
literals[u"__mode__"] = 31
literals[u"__asm"] = 91
literals[u"dynamic_cast"] = 126
literals[u"try"] = 87
literals[u"__cdecl"] = 132
literals[u"register"] = 34
literals[u"auto"] = 33
literals[u"enum"] = 8
literals[u"goto"] = 83
literals[u"int"] = 43
literals[u"for"] = 82
literals[u"char"] = 39
literals[u"friend"] = 24
literals[u"private"] = 66
literals[u"__near"] = 134
literals[u"_stdcall"] = 25
literals[u"class"] = 55
literals[u"this"] = 59
literals[u"__far"] = 136
literals[u"static"] = 35
literals[u"operator"] = 58
literals[u"using"] = 89
literals[u"typename"] = 27
literals[u"throw"] = 74
literals[u"float"] = 50
literals[u"const"] = 32
literals[u"continue"] = 84
literals[u"__attribute__"] = 28
literals[u"reinterpret_cast"] = 128
literals[u"bool"] = 41
literals[u"template"] = 4
literals[u"struct"] = 56
literals[u"__pascal"] = 140
literals[u"signed"] = 48
literals[u"else"] = 78
literals[u"_pascal"] = 139
literals[u"void"] = 52
literals[u"wchar_t"] = 40
literals[u"switch"] = 79
literals[u"true"] = 60
literals[u"__inline"] = 21
literals[u"long"] = 47
literals[u"asm"] = 93
literals[u"virtual"] = 22
literals[u"break"] = 85
literals[u"while"] = 80
literals[u"short"] = 42


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

class Lexer(antlr.CharScanner) :
    ### user action >>>
    lineObject = LineObject()
    originalSource = ""
    deferredLineCount = 0
    
    _line = 0
    
    def setOriginalSource(src):
       originalSource = src
       lineObject.setSource(src)
    
    def setSource(src):
       lineObject.setSource(src)
     
    
    def deferredNewline():
       deferredLineCount += 1
    ### user action <<<
    def __init__(self, *argv, **kwargs) :
        antlr.CharScanner.__init__(self, *argv, **kwargs)
        self.caseSensitiveLiterals = True
        self.setCaseSensitive(True)
        self.literals = literals
        ### __init__ header action >>> 
        self.line_directive_handler = kwargs.get("line_directive_handler")
        ### __init__ header action <<< 
    
    def nextToken(self):
        while True:
            try: ### try again ..
                while True:
                    _token = None
                    _ttype = INVALID_TYPE
                    self.resetText()
                    try: ## for char stream error handling
                        try: ##for lexical error handling
                            la1 = self.LA(1)
                            if False:
                                pass
                            elif la1 and la1 in u',':
                                pass
                                self.mCOMMA(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'?':
                                pass
                                self.mQUESTIONMARK(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u';':
                                pass
                                self.mSEMICOLON(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'(':
                                pass
                                self.mLPAREN(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u')':
                                pass
                                self.mRPAREN(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'[':
                                pass
                                self.mLSQUARE(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u']':
                                pass
                                self.mRSQUARE(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'{':
                                pass
                                self.mLCURLY(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'}':
                                pass
                                self.mRCURLY(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'~':
                                pass
                                self.mTILDE(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'\t\n\u000c\r \\':
                                pass
                                self.mWhitespace(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'"':
                                pass
                                self.mStringLiteral(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'\'':
                                pass
                                self.mCharLiteral(True)
                                theRetToken = self._returnToken
                            elif la1 and la1 in u'ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz':
                                pass
                                self.mID(True)
                                theRetToken = self._returnToken
                            else:
                                if (self.LA(1)==u'>') and (self.LA(2)==u'>') and (self.LA(3)==u'='):
                                    pass
                                    self.mSHIFTRIGHTEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'<') and (self.LA(2)==u'<') and (self.LA(3)==u'='):
                                    pass
                                    self.mSHIFTLEFTEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'-') and (self.LA(2)==u'>') and (self.LA(3)==u'*'):
                                    pass
                                    self.mPOINTERTOMBR(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'-') and (self.LA(2)==u'>') and (True):
                                    pass
                                    self.mPOINTERTO(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'=') and (self.LA(2)==u'='):
                                    pass
                                    self.mEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'!') and (self.LA(2)==u'='):
                                    pass
                                    self.mNOTEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'<') and (self.LA(2)==u'='):
                                    pass
                                    self.mLESSTHANOREQUALTO(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'>') and (self.LA(2)==u'='):
                                    pass
                                    self.mGREATERTHANOREQUALTO(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'/') and (self.LA(2)==u'='):
                                    pass
                                    self.mDIVIDEEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'+') and (self.LA(2)==u'='):
                                    pass
                                    self.mPLUSEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'+') and (self.LA(2)==u'+'):
                                    pass
                                    self.mPLUSPLUS(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'-') and (self.LA(2)==u'='):
                                    pass
                                    self.mMINUSEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'-') and (self.LA(2)==u'-'):
                                    pass
                                    self.mMINUSMINUS(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'*') and (self.LA(2)==u'='):
                                    pass
                                    self.mTIMESEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'%') and (self.LA(2)==u'='):
                                    pass
                                    self.mMODEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'>') and (self.LA(2)==u'>') and (True):
                                    pass
                                    self.mSHIFTRIGHT(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'<') and (self.LA(2)==u'<') and (True):
                                    pass
                                    self.mSHIFTLEFT(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'&') and (self.LA(2)==u'&'):
                                    pass
                                    self.mAND(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'|') and (self.LA(2)==u'|'):
                                    pass
                                    self.mOR(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'&') and (self.LA(2)==u'='):
                                    pass
                                    self.mBITWISEANDEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'|') and (self.LA(2)==u'='):
                                    pass
                                    self.mBITWISEOREQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'^') and (self.LA(2)==u'='):
                                    pass
                                    self.mBITWISEXOREQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'.') and (self.LA(2)==u'*'):
                                    pass
                                    self.mDOTMBR(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u':') and (self.LA(2)==u':'):
                                    pass
                                    self.mSCOPE(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'/') and (self.LA(2)==u'*'):
                                    pass
                                    self.mComment(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'/') and (self.LA(2)==u'/'):
                                    pass
                                    self.mCPPComment(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'#') and (_tokenSet_0.member(self.LA(2))):
                                    pass
                                    self.mPREPROC_DIRECTIVE(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'#') and (self.LA(2)==u'p'):
                                    pass
                                    self.mPragma(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'#') and (self.LA(2)==u'e'):
                                    pass
                                    self.mError(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'=') and (True):
                                    pass
                                    self.mASSIGNEQUAL(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u':') and (True):
                                    pass
                                    self.mCOLON(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'<') and (True):
                                    pass
                                    self.mLESSTHAN(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'>') and (True):
                                    pass
                                    self.mGREATERTHAN(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'/') and (True):
                                    pass
                                    self.mDIVIDE(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'+') and (True):
                                    pass
                                    self.mPLUS(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'-') and (True):
                                    pass
                                    self.mMINUS(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'*') and (True):
                                    pass
                                    self.mSTAR(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'%') and (True):
                                    pass
                                    self.mMOD(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'!') and (True):
                                    pass
                                    self.mNOT(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'&') and (True):
                                    pass
                                    self.mAMPERSAND(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'|') and (True):
                                    pass
                                    self.mBITWISEOR(True)
                                    theRetToken = self._returnToken
                                elif (self.LA(1)==u'^') and (True):
                                    pass
                                    self.mBITWISEXOR(True)
                                    theRetToken = self._returnToken
                                elif (_tokenSet_1.member(self.LA(1))) and (True):
                                    pass
                                    self.mNumber(True)
                                    theRetToken = self._returnToken
                                else:
                                    self.default(self.LA(1))
                                
                            if not self._returnToken:
                                raise antlr.TryAgain ### found SKIP token
                            ### option { testLiterals=true } 
                            self.testForLiteral(self._returnToken)
                            ### return token to caller
                            return self._returnToken
                        ### handle lexical errors ....
                        except antlr.RecognitionException, e:
                            raise antlr.TokenStreamRecognitionException(e)
                    ### handle char stream errors ...
                    except antlr.CharStreamException,cse:
                        if isinstance(cse, antlr.CharStreamIOException):
                            raise antlr.TokenStreamIOException(cse.io)
                        else:
                            raise antlr.TokenStreamException(str(cse))
            except antlr.TryAgain:
                pass
        
    def mASSIGNEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = ASSIGNEQUAL
        _saveIndex = 0
        pass
        self.match('=')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mCOLON(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = COLON
        _saveIndex = 0
        pass
        self.match(':')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mCOMMA(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = COMMA
        _saveIndex = 0
        pass
        self.match(',')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mQUESTIONMARK(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = QUESTIONMARK
        _saveIndex = 0
        pass
        self.match('?')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSEMICOLON(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = SEMICOLON
        _saveIndex = 0
        pass
        self.match(';')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPOINTERTO(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = POINTERTO
        _saveIndex = 0
        pass
        self.match("->")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLPAREN(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LPAREN
        _saveIndex = 0
        pass
        self.match('(')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mRPAREN(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = RPAREN
        _saveIndex = 0
        pass
        self.match(')')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLSQUARE(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LSQUARE
        _saveIndex = 0
        pass
        self.match('[')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mRSQUARE(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = RSQUARE
        _saveIndex = 0
        pass
        self.match(']')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLCURLY(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LCURLY
        _saveIndex = 0
        pass
        self.match('{')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mRCURLY(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = RCURLY
        _saveIndex = 0
        pass
        self.match('}')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = EQUAL
        _saveIndex = 0
        pass
        self.match("==")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mNOTEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = NOTEQUAL
        _saveIndex = 0
        pass
        self.match("!=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLESSTHANOREQUALTO(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LESSTHANOREQUALTO
        _saveIndex = 0
        pass
        self.match("<=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLESSTHAN(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LESSTHAN
        _saveIndex = 0
        pass
        self.match("<")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mGREATERTHANOREQUALTO(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = GREATERTHANOREQUALTO
        _saveIndex = 0
        pass
        self.match(">=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mGREATERTHAN(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = GREATERTHAN
        _saveIndex = 0
        pass
        self.match(">")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mDIVIDE(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = DIVIDE
        _saveIndex = 0
        pass
        self.match('/')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mDIVIDEEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = DIVIDEEQUAL
        _saveIndex = 0
        pass
        self.match("/=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPLUS(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = PLUS
        _saveIndex = 0
        pass
        self.match('+')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPLUSEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = PLUSEQUAL
        _saveIndex = 0
        pass
        self.match("+=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPLUSPLUS(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = PLUSPLUS
        _saveIndex = 0
        pass
        self.match("++")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mMINUS(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = MINUS
        _saveIndex = 0
        pass
        self.match('-')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mMINUSEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = MINUSEQUAL
        _saveIndex = 0
        pass
        self.match("-=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mMINUSMINUS(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = MINUSMINUS
        _saveIndex = 0
        pass
        self.match("--")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSTAR(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = STAR
        _saveIndex = 0
        pass
        self.match('*')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mTIMESEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = TIMESEQUAL
        _saveIndex = 0
        pass
        self.match("*=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mMOD(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = MOD
        _saveIndex = 0
        pass
        self.match('%')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mMODEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = MODEQUAL
        _saveIndex = 0
        pass
        self.match("%=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSHIFTRIGHT(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = SHIFTRIGHT
        _saveIndex = 0
        pass
        self.match(">>")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSHIFTRIGHTEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = SHIFTRIGHTEQUAL
        _saveIndex = 0
        pass
        self.match(">>=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSHIFTLEFT(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = SHIFTLEFT
        _saveIndex = 0
        pass
        self.match("<<")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSHIFTLEFTEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = SHIFTLEFTEQUAL
        _saveIndex = 0
        pass
        self.match("<<=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mAND(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = AND
        _saveIndex = 0
        pass
        self.match("&&")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mNOT(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = NOT
        _saveIndex = 0
        pass
        self.match('!')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mOR(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = OR
        _saveIndex = 0
        pass
        self.match("||")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mAMPERSAND(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = AMPERSAND
        _saveIndex = 0
        pass
        self.match('&')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mBITWISEANDEQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = BITWISEANDEQUAL
        _saveIndex = 0
        pass
        self.match("&=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mTILDE(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = TILDE
        _saveIndex = 0
        pass
        self.match('~')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mBITWISEOR(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = BITWISEOR
        _saveIndex = 0
        pass
        self.match('|')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mBITWISEOREQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = BITWISEOREQUAL
        _saveIndex = 0
        pass
        self.match("|=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mBITWISEXOR(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = BITWISEXOR
        _saveIndex = 0
        pass
        self.match('^')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mBITWISEXOREQUAL(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = BITWISEXOREQUAL
        _saveIndex = 0
        pass
        self.match("^=")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPOINTERTOMBR(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = POINTERTOMBR
        _saveIndex = 0
        pass
        self.match("->*")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mDOTMBR(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = DOTMBR
        _saveIndex = 0
        pass
        self.match(".*")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSCOPE(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = SCOPE
        _saveIndex = 0
        pass
        self.match("::")
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mWhitespace(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Whitespace
        _saveIndex = 0
        pass
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'\t\u000c ':
            pass
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in u' ':
                pass
                self.match(' ')
            elif la1 and la1 in u'\t':
                pass
                self.match('\t')
            elif la1 and la1 in u'\u000c':
                pass
                self.match('\f')
            else:
                    self.raise_NoViableAlt(self.LA(1))
                
        elif la1 and la1 in u'\n\r':
            pass
            if (self.LA(1)==u'\r') and (self.LA(2)==u'\n'):
                pass
                self.match("\r\n")
            elif (self.LA(1)==u'\r') and (True):
                pass
                self.match('\r')
            elif (self.LA(1)==u'\n'):
                pass
                self.match('\n')
            else:
                self.raise_NoViableAlt(self.LA(1))
            
            if not self.inputState.guessing:
                self.newline();
        elif la1 and la1 in u'\\':
            pass
            if (self.LA(1)==u'\\') and (self.LA(2)==u'\r') and (self.LA(3)==u'\n'):
                pass
                self.match("\\\r\n")
            elif (self.LA(1)==u'\\') and (self.LA(2)==u'\r') and (True):
                pass
                self.match("\\\r")
            elif (self.LA(1)==u'\\') and (self.LA(2)==u'\n'):
                pass
                self.match("\\\n")
            else:
                self.raise_NoViableAlt(self.LA(1))
            
            if not self.inputState.guessing:
                deferredNewline()
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        if not self.inputState.guessing:
            _ttype = SKIP
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mComment(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Comment
        _saveIndex = 0
        pass
        self.match("/*")
        while True:
            if ((self.LA(1)==u'*') and ((self.LA(2) >= u'\u0000' and self.LA(2) <= u'\u00ff')) and ((self.LA(3) >= u'\u0000' and self.LA(3) <= u'\u00ff')) and (self.LA(2) != '/')):
                pass
                self.match('*')
            elif (self.LA(1)==u'\n' or self.LA(1)==u'\r'):
                pass
                self.mEndOfLine(False)
                if not self.inputState.guessing:
                    deferredNewline();
            elif (_tokenSet_2.member(self.LA(1))):
                pass
                self.match(_tokenSet_2)
            else:
                break
            
        self.match("*/")
        if not self.inputState.guessing:
            _ttype = SKIP
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mEndOfLine(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = EndOfLine
        _saveIndex = 0
        pass
        if (self.LA(1)==u'\r') and (self.LA(2)==u'\n') and (True):
            pass
            self.match("\r\n")
        elif (self.LA(1)==u'\r') and (True) and (True):
            pass
            self.match('\r')
        elif (self.LA(1)==u'\n'):
            pass
            self.match('\n')
        else:
            self.raise_NoViableAlt(self.LA(1))
        
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mCPPComment(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = CPPComment
        _saveIndex = 0
        pass
        self.match("//")
        while True:
            if (_tokenSet_3.member(self.LA(1))):
                pass
                self.match(_tokenSet_3)
            else:
                break
            
        self.mEndOfLine(False)
        if not self.inputState.guessing:
            _ttype = SKIP; self.newline();
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPREPROC_DIRECTIVE(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = PREPROC_DIRECTIVE
        _saveIndex = 0
        pass
        self.match('#')
        self.mLineDirective(False)
        if not self.inputState.guessing:
            _ttype = SKIP; self.newline();
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLineDirective(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LineDirective
        _saveIndex = 0
        n = None
        sl = None
        pass
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'l':
            pass
            self.match("line")
        elif la1 and la1 in u'\t\u000c ':
            pass
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        _cnt551= 0
        while True:
            if (self.LA(1)==u'\t' or self.LA(1)==u'\u000c' or self.LA(1)==u' '):
                pass
                self.mSpace(False)
            else:
                break
            
            _cnt551 += 1
        if _cnt551 < 1:
            self.raise_NoViableAlt(self.LA(1))
        self.mDecimal(True)
        n = self._returnToken
        _cnt553= 0
        while True:
            if (self.LA(1)==u'\t' or self.LA(1)==u'\u000c' or self.LA(1)==u' '):
                pass
                self.mSpace(False)
            else:
                break
            
            _cnt553 += 1
        if _cnt553 < 1:
            self.raise_NoViableAlt(self.LA(1))
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'"':
            pass
            self.mStringLiteral(True)
            sl = self._returnToken
        elif la1 and la1 in u'\n\r':
            pass
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        if not self.inputState.guessing:
            self.line_directive_handler(sl.getText(), n.getText())  # see main()
        self.mEndOfLine(False)
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mSpace(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Space
        _saveIndex = 0
        pass
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u' ':
            pass
            self.match(' ')
        elif la1 and la1 in u'\t':
            pass
            self.match('\t')
        elif la1 and la1 in u'\u000c':
            pass
            self.match('\f')
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mDecimal(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Decimal
        _saveIndex = 0
        pass
        _cnt589= 0
        while True:
            if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                pass
                self.matchRange(u'0', u'9')
            else:
                break
            
            _cnt589 += 1
        if _cnt589 < 1:
            self.raise_NoViableAlt(self.LA(1))
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mStringLiteral(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = StringLiteral
        _saveIndex = 0
        pass
        self.match('"')
        while True:
            if (self.LA(1)==u'\\') and (_tokenSet_4.member(self.LA(2))):
                pass
                self.mEscape(False)
            elif (self.LA(1)==u'\\') and (self.LA(2)==u'\n' or self.LA(2)==u'\r'):
                pass
                if (self.LA(1)==u'\\') and (self.LA(2)==u'\r') and (self.LA(3)==u'\n'):
                    pass
                    self.match("\\\r\n")
                elif (self.LA(1)==u'\\') and (self.LA(2)==u'\r') and (_tokenSet_3.member(self.LA(3))):
                    pass
                    self.match("\\\r")
                elif (self.LA(1)==u'\\') and (self.LA(2)==u'\n'):
                    pass
                    self.match("\\\n")
                else:
                    self.raise_NoViableAlt(self.LA(1))
                
                if not self.inputState.guessing:
                    deferredNewline();
            elif (_tokenSet_5.member(self.LA(1))):
                pass
                self.match(_tokenSet_5)
            else:
                break
            
        self.match('"')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mPragma(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Pragma
        _saveIndex = 0
        pass
        pass
        self.match('#')
        self.match("pragma")
        while True:
            if (_tokenSet_3.member(self.LA(1))):
                pass
                self.match(_tokenSet_3)
            else:
                break
            
        self.mEndOfLine(False)
        if not self.inputState.guessing:
            _ttype = SKIP; self.newline();
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mError(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Error
        _saveIndex = 0
        pass
        pass
        self.match('#')
        self.match("error")
        while True:
            if (_tokenSet_3.member(self.LA(1))):
                pass
                self.match(_tokenSet_3)
            else:
                break
            
        self.mEndOfLine(False)
        if not self.inputState.guessing:
            _ttype = SKIP; self.newline();
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mCharLiteral(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = CharLiteral
        _saveIndex = 0
        pass
        self.match('\'')
        if (self.LA(1)==u'\\') and (_tokenSet_4.member(self.LA(2))) and (_tokenSet_6.member(self.LA(3))):
            pass
            self.mEscape(False)
        elif (_tokenSet_7.member(self.LA(1))) and (self.LA(2)==u'\'') and (True):
            pass
            self.match(_tokenSet_7)
        else:
            self.raise_NoViableAlt(self.LA(1))
        
        self.match('\'')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mEscape(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Escape
        _saveIndex = 0
        pass
        self.match('\\')
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'a':
            pass
            self.match('a')
        elif la1 and la1 in u'b':
            pass
            self.match('b')
        elif la1 and la1 in u'f':
            pass
            self.match('f')
        elif la1 and la1 in u'n':
            pass
            self.match('n')
        elif la1 and la1 in u'r':
            pass
            self.match('r')
        elif la1 and la1 in u't':
            pass
            self.match('t')
        elif la1 and la1 in u'v':
            pass
            self.match('v')
        elif la1 and la1 in u'"':
            pass
            self.match('"')
        elif la1 and la1 in u'\'':
            pass
            self.match('\'')
        elif la1 and la1 in u'\\':
            pass
            self.match('\\')
        elif la1 and la1 in u'?':
            pass
            self.match('?')
        elif la1 and la1 in u'0123':
            pass
            pass
            self.matchRange(u'0', u'3')
            if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')) and (_tokenSet_3.member(self.LA(2))) and (True):
                pass
                self.mDigit(False)
                if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')) and (_tokenSet_3.member(self.LA(2))) and (True):
                    pass
                    self.mDigit(False)
                elif (_tokenSet_3.member(self.LA(1))) and (True) and (True):
                    pass
                else:
                    self.raise_NoViableAlt(self.LA(1))
                
            elif (_tokenSet_3.member(self.LA(1))) and (True) and (True):
                pass
            else:
                self.raise_NoViableAlt(self.LA(1))
            
        elif la1 and la1 in u'4567':
            pass
            pass
            self.matchRange(u'4', u'7')
            if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')) and (_tokenSet_3.member(self.LA(2))) and (True):
                pass
                self.mDigit(False)
            elif (_tokenSet_3.member(self.LA(1))) and (True) and (True):
                pass
            else:
                self.raise_NoViableAlt(self.LA(1))
            
        elif la1 and la1 in u'x':
            pass
            self.match('x')
            _cnt585= 0
            while True:
                if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')) and (_tokenSet_3.member(self.LA(2))) and (True):
                    pass
                    self.mDigit(False)
                elif ((self.LA(1) >= u'a' and self.LA(1) <= u'f')) and (_tokenSet_3.member(self.LA(2))) and (True):
                    pass
                    self.matchRange(u'a', u'f')
                elif ((self.LA(1) >= u'A' and self.LA(1) <= u'F')) and (_tokenSet_3.member(self.LA(2))) and (True):
                    pass
                    self.matchRange(u'A', u'F')
                else:
                    break
                
                _cnt585 += 1
            if _cnt585 < 1:
                self.raise_NoViableAlt(self.LA(1))
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mDigit(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Digit
        _saveIndex = 0
        pass
        self.matchRange(u'0', u'9')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mLongSuffix(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = LongSuffix
        _saveIndex = 0
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'l':
            pass
            self.match('l')
        elif la1 and la1 in u'L':
            pass
            self.match('L')
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mUnsignedSuffix(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = UnsignedSuffix
        _saveIndex = 0
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'u':
            pass
            self.match('u')
        elif la1 and la1 in u'U':
            pass
            self.match('U')
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mFloatSuffix(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = FloatSuffix
        _saveIndex = 0
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'f':
            pass
            self.match('f')
        elif la1 and la1 in u'F':
            pass
            self.match('F')
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mExponent(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Exponent
        _saveIndex = 0
        pass
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'e':
            pass
            self.match('e')
        elif la1 and la1 in u'E':
            pass
            self.match('E')
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'+':
            pass
            self.match('+')
        elif la1 and la1 in u'-':
            pass
            self.match('-')
        elif la1 and la1 in u'0123456789':
            pass
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        _cnt597= 0
        while True:
            if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                pass
                self.mDigit(False)
            else:
                break
            
            _cnt597 += 1
        if _cnt597 < 1:
            self.raise_NoViableAlt(self.LA(1))
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mVocabulary(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Vocabulary
        _saveIndex = 0
        pass
        self.matchRange(u'\3', u'\377')
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mNumber(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = Number
        _saveIndex = 0
        synPredMatched604 = False
        if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')) and (_tokenSet_8.member(self.LA(2))) and (True):
            _m604 = self.mark()
            synPredMatched604 = True
            self.inputState.guessing += 1
            try:
                pass
                _cnt602= 0
                while True:
                    if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                        pass
                        self.mDigit(False)
                    else:
                        break
                    
                    _cnt602 += 1
                if _cnt602 < 1:
                    self.raise_NoViableAlt(self.LA(1))
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in u'.':
                    pass
                    self.match('.')
                elif la1 and la1 in u'e':
                    pass
                    self.match('e')
                elif la1 and la1 in u'E':
                    pass
                    self.match('E')
                else:
                        self.raise_NoViableAlt(self.LA(1))
                    
            except antlr.RecognitionException, pe:
                synPredMatched604 = False
            self.rewind(_m604)
            self.inputState.guessing -= 1
        if synPredMatched604:
            pass
            _cnt606= 0
            while True:
                if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                    pass
                    self.mDigit(False)
                else:
                    break
                
                _cnt606 += 1
            if _cnt606 < 1:
                self.raise_NoViableAlt(self.LA(1))
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in u'.':
                pass
                self.match('.')
                while True:
                    if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                        pass
                        self.mDigit(False)
                    else:
                        break
                    
                if (self.LA(1)==u'E' or self.LA(1)==u'e'):
                    pass
                    self.mExponent(False)
                else: ## <m4>
                        pass
                    
                if not self.inputState.guessing:
                    _ttype = FLOATONE;
            elif la1 and la1 in u'Ee':
                pass
                self.mExponent(False)
                if not self.inputState.guessing:
                    _ttype = FLOATTWO;
            else:
                    self.raise_NoViableAlt(self.LA(1))
                
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in u'Ff':
                pass
                self.mFloatSuffix(False)
            elif la1 and la1 in u'Ll':
                pass
                self.mLongSuffix(False)
            else:
                ##<m3> <closing
                    pass
                
        else:
            synPredMatched613 = False
            if (self.LA(1)==u'.') and (self.LA(2)==u'.'):
                _m613 = self.mark()
                synPredMatched613 = True
                self.inputState.guessing += 1
                try:
                    pass
                    self.match("...")
                except antlr.RecognitionException, pe:
                    synPredMatched613 = False
                self.rewind(_m613)
                self.inputState.guessing -= 1
            if synPredMatched613:
                pass
                self.match("...")
                if not self.inputState.guessing:
                    _ttype = ELLIPSIS;
            elif (self.LA(1)==u'0') and (self.LA(2)==u'X' or self.LA(2)==u'x'):
                pass
                self.match('0')
                la1 = self.LA(1)
                if False:
                    pass
                elif la1 and la1 in u'x':
                    pass
                    self.match('x')
                elif la1 and la1 in u'X':
                    pass
                    self.match('X')
                else:
                        self.raise_NoViableAlt(self.LA(1))
                    
                _cnt629= 0
                while True:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in u'abcdef':
                        pass
                        self.matchRange(u'a', u'f')
                    elif la1 and la1 in u'ABCDEF':
                        pass
                        self.matchRange(u'A', u'F')
                    elif la1 and la1 in u'0123456789':
                        pass
                        self.mDigit(False)
                    else:
                            break
                        
                    _cnt629 += 1
                if _cnt629 < 1:
                    self.raise_NoViableAlt(self.LA(1))
                while True:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in u'Ll':
                        pass
                        self.mLongSuffix(False)
                    elif la1 and la1 in u'Uu':
                        pass
                        self.mUnsignedSuffix(False)
                    else:
                            break
                        
                if not self.inputState.guessing:
                    _ttype = HEXADECIMALINT;
            elif (self.LA(1)==u'.') and (True):
                pass
                self.match('.')
                if not self.inputState.guessing:
                    _ttype = DOT;
                if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                    pass
                    _cnt616= 0
                    while True:
                        if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                            pass
                            self.mDigit(False)
                        else:
                            break
                        
                        _cnt616 += 1
                    if _cnt616 < 1:
                        self.raise_NoViableAlt(self.LA(1))
                    if (self.LA(1)==u'E' or self.LA(1)==u'e'):
                        pass
                        self.mExponent(False)
                    else: ## <m4>
                            pass
                        
                    if not self.inputState.guessing:
                        _ttype = FLOATONE;
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in u'Ff':
                        pass
                        self.mFloatSuffix(False)
                    elif la1 and la1 in u'Ll':
                        pass
                        self.mLongSuffix(False)
                    else:
                        ##<m3> <closing
                            pass
                        
                else: ## <m4>
                        pass
                    
            elif (self.LA(1)==u'0') and (True) and (True):
                pass
                self.match('0')
                while True:
                    if ((self.LA(1) >= u'0' and self.LA(1) <= u'7')):
                        pass
                        self.matchRange(u'0', u'7')
                    else:
                        break
                    
                while True:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in u'Ll':
                        pass
                        self.mLongSuffix(False)
                    elif la1 and la1 in u'Uu':
                        pass
                        self.mUnsignedSuffix(False)
                    else:
                            break
                        
                if not self.inputState.guessing:
                    _ttype = OCTALINT;
            elif ((self.LA(1) >= u'1' and self.LA(1) <= u'9')) and (True) and (True):
                pass
                self.matchRange(u'1', u'9')
                while True:
                    if ((self.LA(1) >= u'0' and self.LA(1) <= u'9')):
                        pass
                        self.mDigit(False)
                    else:
                        break
                    
                while True:
                    la1 = self.LA(1)
                    if False:
                        pass
                    elif la1 and la1 in u'Ll':
                        pass
                        self.mLongSuffix(False)
                    elif la1 and la1 in u'Uu':
                        pass
                        self.mUnsignedSuffix(False)
                    else:
                            break
                        
                if not self.inputState.guessing:
                    _ttype = DECIMALINT;
            else:
                self.raise_NoViableAlt(self.LA(1))
            
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    def mID(self, _createToken):    
        _ttype = 0
        _token = None
        _begin = self.text.length()
        _ttype = ID
        _saveIndex = 0
        pass
        la1 = self.LA(1)
        if False:
            pass
        elif la1 and la1 in u'abcdefghijklmnopqrstuvwxyz':
            pass
            self.matchRange(u'a', u'z')
        elif la1 and la1 in u'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
            pass
            self.matchRange(u'A', u'Z')
        elif la1 and la1 in u'_':
            pass
            self.match('_')
        else:
                self.raise_NoViableAlt(self.LA(1))
            
        while True:
            la1 = self.LA(1)
            if False:
                pass
            elif la1 and la1 in u'abcdefghijklmnopqrstuvwxyz':
                pass
                self.matchRange(u'a', u'z')
            elif la1 and la1 in u'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
                pass
                self.matchRange(u'A', u'Z')
            elif la1 and la1 in u'_':
                pass
                self.match('_')
            elif la1 and la1 in u'0123456789':
                pass
                self.matchRange(u'0', u'9')
            else:
                    break
                
        ### option { testLiterals=true } 
        _ttype = self.testLiteralsTable(_ttype)
        self.set_return_token(_createToken, _token, _ttype, _begin)
    
    

### generate bit set
def mk_tokenSet_0(): 
    ### var1
    data = [ 4294971904L, 17592186044416L, 0L, 0L, 0L]
    return data
_tokenSet_0 = antlr.BitSet(mk_tokenSet_0())

### generate bit set
def mk_tokenSet_1(): 
    ### var1
    data = [ 288019269919178752L, 0L, 0L, 0L, 0L]
    return data
_tokenSet_1 = antlr.BitSet(mk_tokenSet_1())

### generate bit set
def mk_tokenSet_2(): 
    data = [0L] * 8 ### init list
    data[0] =-4398046520321L
    for x in xrange(1, 4):
        data[x] = -1L
    return data
_tokenSet_2 = antlr.BitSet(mk_tokenSet_2())

### generate bit set
def mk_tokenSet_3(): 
    data = [0L] * 8 ### init list
    data[0] =-9217L
    for x in xrange(1, 4):
        data[x] = -1L
    return data
_tokenSet_3 = antlr.BitSet(mk_tokenSet_3())

### generate bit set
def mk_tokenSet_4(): 
    ### var1
    data = [ -9151595350857875456L, 95772161741946880L, 0L, 0L, 0L]
    return data
_tokenSet_4 = antlr.BitSet(mk_tokenSet_4())

### generate bit set
def mk_tokenSet_5(): 
    data = [0L] * 8 ### init list
    data[0] =-17179878401L
    data[1] =-268435457L
    for x in xrange(2, 4):
        data[x] = -1L
    return data
_tokenSet_5 = antlr.BitSet(mk_tokenSet_5())

### generate bit set
def mk_tokenSet_6(): 
    ### var1
    data = [ 287949450930814976L, 541165879422L, 0L, 0L, 0L]
    return data
_tokenSet_6 = antlr.BitSet(mk_tokenSet_6())

### generate bit set
def mk_tokenSet_7(): 
    data = [0L] * 8 ### init list
    data[0] =-549755813889L
    for x in xrange(1, 4):
        data[x] = -1L
    return data
_tokenSet_7 = antlr.BitSet(mk_tokenSet_7())

### generate bit set
def mk_tokenSet_8(): 
    ### var1
    data = [ 288019269919178752L, 137438953504L, 0L, 0L, 0L]
    return data
_tokenSet_8 = antlr.BitSet(mk_tokenSet_8())
    
### __main__ header action >>> 
if __name__ == '__main__' :
    import sys
    import antlr
    import CPPLexer
    
    ### create lexer - shall read from stdin
    try:
        for token in CPPLexer.Lexer():
            print token
            
    except antlr.TokenStreamException, e:
        print "error: exception caught while lexing: ", e
### __main__ header action <<< 
