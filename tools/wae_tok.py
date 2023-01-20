#!/usr/bin/python

import string

class tokeniser:

	def __init__( self, eots ):
		self.eots = eots
		self.tokens = []
		
	# create an escapte character
	def esc_char( self, ch ):
		if( ch == "\"" or ch == "\\" ):
			return ch
		else:
			return "?"

	# is a char whitespace?
	def is_a( self, a, ch ):
		return string.find( a, ch ) != -1
	
	# is a char whitespace?
	def is_white( self, ch ):
		return self.is_a( string.whitespace, ch )

	# is char an end of token?
	def is_eot( self, ch ):
		if( self.is_white( ch ) ):
			return 1
		if( self.is_a( self.eots, ch ) ):
			return 1

		return 0
		
	def eat_string_literal( self, s ):
		idx = 1  # skip leading "
		tok = ""
		while( 1 ):
			cur = s[idx]
			if( cur == "\"" ):
				break
			if( tok == "\\" ):
				idx = idx + 1
				cur = esc_char( s[idx] )
				
			tok = tok + cur
			idx = idx + 1
			
		self.tokens.append( "\"" + tok + "\"" )
		return idx + 1
		
	def eat_whitespace( self, s ):
		# just skip one-by-one and don't add any tokens
		return 1
	
	def eat_token( self, s ):
		if( self.is_eot( s[0] ) ):
			self.tokens.append( s[0] )
			return 1

		tok = ""
		idx = 0
		while( idx < len( s )  ):
			cur = s[idx]
			if( self.is_eot(cur) ):
				break
			tok = tok + cur
			idx = idx + 1

		self.tokens.append( tok )
		return idx

	def tokenise( self, line ):
		idx = 0
		while idx < len( line ):
			cur = line[idx]
			
			if( cur == "\"" ):
 				idx = idx + self.eat_string_literal( line[idx:] )
			elif( self.is_white( cur ) ):
				idx = idx + self.eat_whitespace( line[idx:] )
			else:
				idx = idx + self.eat_token( line[idx:] )

		#for each in self.tokens:
		#	print "%s" % each

if __name__ == "__main__":
	t = tokeniser("@<>:()*+")
	s = "atoi(\"37.69 b\") + 57*8.5"
	print "about to tokenise '%s'" % s 
	t.tokenise( s )
	print t.tokens

	t.tokens = []
	s = "pants 32@0x1230 : "
	print "about to tokenise '%s'" % s 
	t.tokenise( s )
	print t.tokens

	t.tokens = []
	s = "pants 32 @ 1230 : "
	print "about to tokenise '%s'" % s 
	t.tokenise( s )
	print t.tokens
