// Scintilla source code edit control
/** @file KeyWords.cxx
 ** Colourise for particular languages.
 **/
// Copyright 1998-2002 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "KeyWords.h"
#include "Scintilla.h"
#include "SciLexer.h"

const LexerModule *LexerModule::base = 0;
int LexerModule::nextLanguage = SCLEX_AUTOMATIC+1;

LexerModule::LexerModule(int language_, LexerFunction fnLexer_,
	const char *languageName_, LexerFunction fnFolder_,
	const char * const wordListDescriptions_[]) :
	language(language_),
	fnLexer(fnLexer_),
	fnFolder(fnFolder_),
	wordListDescriptions(wordListDescriptions_),
	languageName(languageName_) {
	next = base;
	base = this;
	if (language == SCLEX_AUTOMATIC) {
		language = nextLanguage;
		nextLanguage++;
	}
}

int LexerModule::GetNumWordLists() const {
	if (wordListDescriptions == NULL) {
		return -1;
	} else {
		int numWordLists = 0;

		while (wordListDescriptions[numWordLists]) {
			++numWordLists;
		}

		return numWordLists;
	}
}

const char * LexerModule::GetWordListDescription(int index) const {
	static const char *emptyStr = "";

	PLATFORM_ASSERT(index < GetNumWordLists());
	if (index >= GetNumWordLists()) {
		return emptyStr;
	} else {
		return wordListDescriptions[index];
 	}
}

const LexerModule *LexerModule::Find(int language) {
	const LexerModule *lm = base;
	while (lm) {
		if (lm->language == language) {
			return lm;
		}
		lm = lm->next;
	}
	return 0;
}

const LexerModule *LexerModule::Find(const char *languageName) {
	if (languageName) {
		const LexerModule *lm = base;
		while (lm) {
			if (lm->languageName && 0 == strcmp(lm->languageName, languageName)) {
				return lm;
			}
			lm = lm->next;
		}
	}
	return 0;
}

void LexerModule::Lex(unsigned int startPos, int lengthDoc, int initStyle,
	  WordList *keywordlists[], Accessor &styler) const {
	if (fnLexer)
		fnLexer(startPos, lengthDoc, initStyle, keywordlists, styler);
}

void LexerModule::Fold(unsigned int startPos, int lengthDoc, int initStyle,
	  WordList *keywordlists[], Accessor &styler) const {
	if (fnFolder) {
		int lineCurrent = styler.GetLine(startPos);
		// Move back one line in case deletion wrecked current line fold state
		if (lineCurrent > 0) {
			lineCurrent--;
			int newStartPos = styler.LineStart(lineCurrent);
			lengthDoc += startPos - newStartPos;
			startPos = newStartPos;
			initStyle = 0;
			if (startPos > 0) {
				initStyle = styler.StyleAt(startPos - 1);
			}
		}
		fnFolder(startPos, lengthDoc, initStyle, keywordlists, styler);
	}
}

static void ColouriseNullDoc(unsigned int startPos, int length, int, WordList *[],
                            Accessor &styler) {
	// Null language means all style bytes are 0 so just mark the end - no need to fill in.
	if (length > 0) {
		styler.StartAt(startPos + length - 1);
		styler.StartSegment(startPos + length - 1);
		styler.ColourTo(startPos + length - 1, 0);
	}
}

LexerModule lmNull(SCLEX_NULL, ColouriseNullDoc, "null");

// Alternative historical name for Scintilla_LinkLexers
int wxForceScintillaLexers(void) {
	return Scintilla_LinkLexers();
}

// To add or remove a lexer, add or remove its file and run LexGen.py.

// Force a reference to all of the Scintilla lexers so that the linker will
// not remove the code of the lexers.
int Scintilla_LinkLexers() {
	static int forcer = 0;

// Shorten the code that declares a lexer and ensures it is linked in by calling a method.
#define LINK_LEXER(lexer) extern LexerModule lexer; forcer += lexer.GetLanguage();

//++Autogenerated -- run src/LexGen.py to regenerate
//**\(\tLINK_LEXER(\*);\n\)
	LINK_LEXER(lmAda);
	LINK_LEXER(lmAsm);
	LINK_LEXER(lmAVE);
	LINK_LEXER(lmBaan);
	LINK_LEXER(lmBullant);
	LINK_LEXER(lmConf);
	LINK_LEXER(lmCPP);
	LINK_LEXER(lmCPPNoCase);
	LINK_LEXER(lmTCL);
	LINK_LEXER(lmNncrontab);
	LINK_LEXER(lmCss);
	LINK_LEXER(lmEiffel);
	LINK_LEXER(lmEiffelkw);
	LINK_LEXER(lmFortran);
	LINK_LEXER(lmF77);
	LINK_LEXER(lmHTML);
	LINK_LEXER(lmXML);
	LINK_LEXER(lmASP);
	LINK_LEXER(lmPHP);
	LINK_LEXER(lmLISP);
	LINK_LEXER(lmLua);
	LINK_LEXER(lmMatlab);
	LINK_LEXER(lmBatch);
	LINK_LEXER(lmDiff);
	LINK_LEXER(lmProps);
	LINK_LEXER(lmMake);
	LINK_LEXER(lmErrorList);
	LINK_LEXER(lmLatex);
	LINK_LEXER(lmPascal);
	LINK_LEXER(lmPerl);
	LINK_LEXER(lmPOV);
	LINK_LEXER(lmPython);
	LINK_LEXER(lmRuby);
	LINK_LEXER(lmSQL);
	LINK_LEXER(lmVB);
	LINK_LEXER(lmVBScript);

//--Autogenerated -- end of automatically generated section

	return 1;
}
