//---------------------------------------------------------------------------
//
//	X68000 EMULATOR "XM6"
//
//	Copyright (C) 2001-2005 ＰＩ．(ytanaka@ipc-tokai.or.jp)
//	Copyright (C) 2013-2019 GIMONS
//	[ ファイルI/O(RaSCSI用サブセット) ]
//
//---------------------------------------------------------------------------

#if !defined(fileio_h)
#define fileio_h

//===========================================================================
//
//	マクロ(Load,Save用)
//
//===========================================================================
#define PROP_IMPORT(f, p) \
	if (!f->Read(&(p), sizeof(p))) {\
		return FALSE;\
	}\

#define PROP_EXPORT(f, p) \
	if (!f->Write(&(p), sizeof(p))) {\
		return FALSE;\
	}\

//===========================================================================
//
//	ファイルI/O
//
//===========================================================================
class Fileio
{
public:
	enum OpenMode {
		ReadOnly,						// 読み込みのみ
		WriteOnly,						// 書き込みのみ
		ReadWrite,						// 読み書き両方
		Append							// アペンド
	};

public:
	Fileio();
										// コンストラクタ
	virtual ~Fileio();
										// デストラクタ
	BOOL FASTCALL Load(const Filepath& path, void *buffer, int size);
										// ROM,RAMロード
	BOOL FASTCALL Save(const Filepath& path, void *buffer, int size);
										// RAMセーブ

	BOOL FASTCALL Open(LPCTSTR fname, OpenMode mode);
										// オープン
	BOOL FASTCALL Open(const Filepath& path, OpenMode mode);
										// オープン
	BOOL FASTCALL OpenDIO(LPCTSTR fname, OpenMode mode);
										// オープン
	BOOL FASTCALL OpenDIO(const Filepath& path, OpenMode mode);
										// オープン
	BOOL FASTCALL Seek(off64_t offset, BOOL relative = FALSE);
										// シーク
	BOOL FASTCALL Read(void *buffer, int size);
										// 読み込み
	BOOL FASTCALL Write(const void *buffer, int size);
										// 書き込み
	off64_t FASTCALL GetFileSize();
										// ファイルサイズ取得
	off64_t FASTCALL GetFilePos() const;
										// ファイル位置取得
	void FASTCALL Close();
										// クローズ
	BOOL FASTCALL IsValid() const		{ return (BOOL)(handle != -1); }
										// 有効チェック
	int FASTCALL GetHandle() const		{ return handle; }
										// ハンドル取得

private:
	BOOL FASTCALL Open(LPCTSTR fname, OpenMode mode, BOOL directIO);
										// オープン

	int handle;							// ファイルハンドル
};

#endif	// fileio_h
