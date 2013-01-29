#include <iostream>
#include <algorithm>
#include <cstring>
#include <iostream>

#include <mmseg/SegmenterManager.h>
#include <mmseg/Segmenter.h>
#include <mmseg/csr_utils.h>

#include "mmseg.h"

using namespace std;
using namespace css;

SegmenterManager *mgr_ = NULL;

int mmseg_init(char *path)
{
	if (!path) {
		return -1;
	}
	if (mgr_) {
		return 0;
	}
	SegmenterManager *mgr = new SegmenterManager();
	int ret = mgr->init(path);
	if (ret != 0) {
		delete mgr;
		cerr << "error: invalid dict path\n";
		return -1;
	}
	mgr_ = mgr;
	return 0;
}

int mmseg_segment(char *text, Token ** tokens)
{
	if (!text) {
		return -1;
	}
	if (!mgr_) {
		cerr << "error: init not called\n";
		return -1;
	}
	Segmenter *seg = mgr_->getSegmenter(0);
	seg->setBuffer((u1 *) text, (u4) strlen(text));

	vector<Token> segs;
	while (1) {
		u2 len = 0, symlen = 0;
		char *token = (char *)seg->peekToken(len, symlen);
		if (!token || !*token || !len) {
			break;
		}
		Token t = {token, int(len)};
		segs.push_back(t);
		seg->popToken(len);
	}
	int size = segs.size();

	if (!tokens) {
		delete seg;
		return size;
	}
	(*tokens) = (Token *) malloc(segs.size() * sizeof(Token));
	int i = 0;
	vector < Token >::iterator iter = segs.begin();
	for (; iter != segs.end(); iter++) {
		(*tokens)[i] = *iter;
		i++;
	}
	delete seg;
	return size;
}

int mmseg_destroy()
{
	delete mgr_;
	mgr_ = NULL;
}

Token *next_token(Token * p)
{
	return ++p;
}
