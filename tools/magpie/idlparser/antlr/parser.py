import sys, types
from cStringIO import StringIO

from IDLLexer import Lexer
#from CPPSymbol import *
import IDLParser
import extendAST

#from enum_types import *
from parser_common import Node, UnfinishedNode

from astgen import gen as ast_gen
from cache import CachedTransformableFile, NotInCacheError

# FIXME: This is sort of retarded, but the generated code doesn't import exceptions before
# using them. So here we manually inject them into its namespace.
#import antlr
#IDLParser.SemanticException = antlr.SemanticException
# FIXME: End of manual namespace update.

def debug_warn(text):
  #print text
  pass

def debug_info(text):
  #print text
  pass

class Parser(IDLParser.Parser):
  """ This Parser class replicates the stuff in Support.cpp. Really, it shouldn't be
  an overloading class, because knows all about the inner workings of its base. But unlike
  C++, Python doesn't let you separate interface and implementation, so I do
  this this way to avoid clogging up the grammar file.
  """
  def __init__(self, *args, **kwargs):
    self.finished = False
    self.nodeinfo = {'depth': 0, 'nodes': []}
    IDLParser.Parser.__init__(self, *args, **kwargs)

  def addASTChild(self,currentAST, child):
    if not child:
      return
      
    rootnode = Node(sys._getframe(1).f_code.co_name) 
    if child.node:
    	if not currentAST.root:
    	  rootnode.children = [child.node]
    	else:
    	  rootnode = child.node # Node(sys._getframe(1).f_code.co_name, children=[child.node])

    child.node = rootnode
    child.node.leaf = child.getText()
   
    if child.node == None:
    	print child
    if not currentAST.root:
      currentAST.root = child
    elif not currentAST.child:
      currentAST.root.setFirstChild(child)
    else:
      currentAST.root.node.add_child(child.node)
      currentAST.child.setNextSibling(child)
      currentAST.child = child
      currentAST.advanceChildToEnd()
"""
    ### wh: moved from ASTFactory to Parser -> Soren: and then to my Parser! :-)
  def makeASTRoot(self,currentAST,root) :
    if root:
      root.node = Node(sys._getframe(1).f_code.co_name)
      root.node.leaf = root.getText()
      
      print 'MAST', root.node.type
      ### Add the current root as a child of new root
      root.addChild(currentAST.root)
      if currentAST.root:
         root.node.add_child(currentAST.root.node)
      ### The new current child is the last sibling of the old root
      currentAST.child = currentAST.root
      currentAST.advanceChildToEnd()
      ### Set the new root
      currentAST.root = root       
      
"""

def parse_to_pt_noncached(data):
  inputhandle = StringIO(data)
  lexer = Lexer(inputhandle)
  parser = Parser(lexer)
  #result = parser.specification()
  #return result.node
  parser.specification()
  return parser.returnAST.node

def parse_to_pt_cached(filename, data):
  cached = CachedTransformableFile(filename, data)
  try:
    pt = cached.load()
  except NotInCacheError:
    pt = parse_to_pt_noncached(data)
    cached.save(pt)
  return pt

def parse_to_ast(pt):
  ast = ast_gen(pt)
  return ast

def parse(filename, data):
  pt = parse_to_pt_cached(filename, data)
  ast = parse_to_ast(pt)
  return ast

def test(inputhandle):
  lexer = Lexer(inputhandle)
  parser = Parser(lexer)
  ast = parser.specification()
  #print '\n\n\n\n', ast
  ast.node.print_tree()
  print '\n\n\n\n', ast
  
if __name__ == '__main__':
  handle = file(sys.argv[1])
  test(handle)
