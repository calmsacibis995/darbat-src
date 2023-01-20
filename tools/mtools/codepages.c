#include "codepage.h"

/* MS-DOS doesn't use the same ASCII code as Unix does. The appearance
 * of the characters is defined using code pages. These code pages
 * aren't the same for all countries. For instance, some code pages
 * don't contain upper case accented characters. This affects two
 * things, relating to filenames:

 * 1. upper case characters. In short names, only upper case
 * characters are allowed.  This also holds for accented characters.
 * For instance, in a code page which doesn't contain accented
 * uppercase characters, the accented lowercase characters get
 * transformed into their unaccented counterparts. This is very bad
 * design. Indeed, stuff like national language support should never
 * affect filesystem integrity. And it does: A filename which is legal
 * in one country could be illegal in another one. Bad News for
 * frequent travellers.

 * 2. long file names: Micro$oft has finally come to their senses and
 * uses a more standard mapping for the long file names.  They use
 * Unicode, which is basically a 32 bit version of ASCII. Its first
 * 256 characters are identical to Unix ASCII. Thus, the code page
 * also affects the correspondence between the codes used in long
 * names and those used in short names.

 * Such a bad design is rather unbelievable. That's why I quoted the
 * translation tables. BEGIN FAIR USE EXCERPT:
 */


Codepage_t codepages[]= {
	{ 437,
	  "����������������"
	  "����������ܢ��Pf"
	  "�����Ѫ��r������"
	  "_______________�"
	  "________________"
	  "________________"
	  "abgpSs�tftod��_N"
	  "=�<>||�~���Vn�__"
	},

	{ 819,
	  "________________"
	  "________________"
	  "����������������"
	  "����������������"
	  "����������������"
	  "����������������"
	  "����������������"
	  "����������������"
	},

	{ 850,
	  "����������������"
	  "���������������_"
	  "�����Ѫ���������"
	  "_____����____���"
	  "______��_______�"
	  "�����i���____|I_"
	  "�����յ������ޯ�"
	  "��_�����������__"
	},
	
	{ 852,
	  "�����uc�l����Z�C"
	  "�Ll��LlSs��TtL�c"
	  "����AaZzEe zCs��"
	  "_____��ES____Zz�"
	  "______Aa_______�"
	  "��D�d���e_r__TU_"
	  "���Nn�SsR�rU��t�"
	  "�~.~~�������uRr_"
	},
	
	{ 860,      
	  "����������������"
	  "����������ܢ��P�"
	  "�����Ѫ��Ҭ�����"
	  "_______________�"
	  "________________"
	  "________________"
	  "abgpSs�tftod��_N"
	  "=�<>||�~���Vn�__"
	},
	
	{ 863,      
	  "������������_��"
	  "����������ܢ���f"
	  "|���� ���r������"
	  "_______________�"
	  "________________"
	  "________________"
	  "abgpSs�tftod��_N"
	  "=�<>||�~���Vn�__"
	},
	
	{ 865,
	  "����������������"
	  "��������������Pf"
	  "�����Ѫ��r������"
	  "_______________�"
	  "________________"
	  "________________"
	  "abgpSs�tftod��_N"
	  "=�<>||�~���Vn�__",
	},

	/* Taiwanese (Chinese Complex Character) support */
	{ 950,
	 "����������������"
	 "����������������"
	 "����������������"
	 "����������������"
	 "����������������"
	 "����������������"
	 "����������������"
	 "����������������",
	},


	{ 0 }
};

/* END FAIR USE EXCERPT */
