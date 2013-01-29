#ifndef MMSEG_GO
#define MMSEG_GO

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct {
		char *Start;
		int Len;
	} Token;

	int mmseg_init(char *path);
	int mmseg_segment(char *text, Token ** segments);
	int mmseg_destroy();
	Token *next_token(Token * p);

#ifdef __cplusplus
}
#endif
#endif
