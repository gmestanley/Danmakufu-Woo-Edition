#ifndef __DIRECTX_SHADER__
#define __DIRECTX_SHADER__

#include "DirectGraphics.hpp"
#include "DxConstant.hpp"
#include "Texture.hpp"

namespace directx {

// http://msdn.microsoft.com/ja-jp/library/bb944006(v=vs.85).aspx
// http://msdn.microsoft.com/ja-jp/library/bb509647(v=vs.85).aspx

class ShaderManager;
class Shader;
class ShaderData;
/**********************************************************
//ShaderData
**********************************************************/
class ShaderData {
	friend Shader;
	friend ShaderManager;

public:
	ShaderData();
	virtual ~ShaderData();
	std::wstring GetName() const { return name_; }

private:
	ShaderManager* manager_;
	ID3DXEffect* effect_;
	std::wstring name_;
	volatile bool bLoad_;
	volatile bool bText_;
};

/**********************************************************
//ShaderManager
**********************************************************/
class ShaderManager : public DirectGraphicsListener {
	friend Shader;
	friend ShaderData;

public:
	ShaderManager();
	~ShaderManager() override;
	static ShaderManager* GetBase() { return thisBase_; }
	virtual bool Initialize();
	gstd::CriticalSection& GetLock() { return lock_; }
	void Clear();

	void ReleaseDirectGraphics() override { ReleaseDxResource(); }
	void RestoreDirectGraphics() override { RestoreDxResource(); }
	void ReleaseDxResource();
	void RestoreDxResource();

	virtual bool IsDataExists(const std::wstring& name) const;
	gstd::ref_count_ptr<ShaderData> GetShaderData(const std::wstring& name);
	gstd::ref_count_ptr<Shader> CreateFromFile(const std::wstring& path); //読み込みます。ShaderDataは保持しますが、Shaderは保持しません。
	gstd::ref_count_ptr<Shader> CreateFromText(const std::string& source); //読み込みます。ShaderDataは保持しますが、Shaderは保持しません。
	gstd::ref_count_ptr<Shader> CreateFromFileInLoadThread(const std::wstring& path);
	virtual void CallFromLoadThread(gstd::ref_count_ptr<gstd::FileManager::LoadThreadEvent> event);

	void AddShader(const std::wstring& name, gstd::ref_count_ptr<Shader> shader);
	void DeleteShader(const std::wstring& name);
	gstd::ref_count_ptr<Shader> GetShader(const std::wstring& name);
	gstd::ref_count_ptr<Shader> GetDefaultSkinnedMeshShader();

	void CheckExecutingShaderZero() const;
	std::wstring GetLastError();

protected:
	mutable gstd::CriticalSection lock_;
	std::map<std::wstring, gstd::ref_count_ptr<Shader>> mapShader_;
	std::map<std::wstring, gstd::ref_count_ptr<ShaderData>> mapShaderData_;

	std::list<Shader*> listExecuteShader_;
	std::wstring lastError_;

	void _ReleaseShaderData(const std::wstring& name);
	bool _CreateFromFile(const std::wstring& path);
	bool _CreateFromText(const std::string& source);
	void _BeginShader(Shader* shader, int pass);
	void _EndShader(Shader* shader);
	static std::wstring _GetTextSourceID(const std::string& source);

private:
	static ShaderManager* thisBase_;
};

/**********************************************************
//ShaderParameter
**********************************************************/
class ShaderParameter {
public:
	enum {
		TYPE_UNKNOWN,
		TYPE_MATRIX,
		TYPE_MATRIX_ARRAY,
		TYPE_VECTOR,
		TYPE_FLOAT,
		TYPE_FLOAT_ARRAY,
		TYPE_TEXTURE,
	};

public:
	ShaderParameter();
	virtual ~ShaderParameter();

	int GetType() const { return type_; }
	void SetMatrix(D3DXMATRIX& matrix);
	D3DXMATRIX GetMatrix();
	void SetMatrixArray(std::vector<D3DXMATRIX>& matrix);
	std::vector<D3DXMATRIX> GetMatrixArray();
	void SetVector(D3DXVECTOR4& vector);
	D3DXVECTOR4 GetVector();
	void SetFloat(float value);
	float GetFloat();
	void SetFloatArray(std::vector<float>& values);
	std::vector<float> GetFloatArray();
	void SetTexture(gstd::ref_count_ptr<Texture> texture);
	gstd::ref_count_ptr<Texture> GetTexture();

private:
	int type_;
	gstd::ref_count_ptr<gstd::ByteBuffer> value_;
	gstd::ref_count_ptr<Texture> texture_;
};

/**********************************************************
//Shader
**********************************************************/
class Shader {
	friend ShaderManager;

public:
	Shader();
	Shader(const Shader* shader);
	virtual ~Shader();
	void Release();

	void Begin(int pass = 0);
	void End();

	ID3DXEffect* GetEffect();
	void ReleaseDxResource();
	void RestoreDxResource();

	bool CreateFromFile(const std::wstring& path);
	bool CreateFromText(const std::string& source);
	bool IsLoad() const { return data_ != nullptr && data_->bLoad_; }

	bool SetTechnique(const std::string& name);
	bool SetMatrix(const std::string& name, D3DXMATRIX& matrix);
	bool SetMatrixArray(const std::string& name, std::vector<D3DXMATRIX>& matrix);
	bool SetVector(const std::string& name, D3DXVECTOR4& vector);
	bool SetFloat(const std::string& name, float value);
	bool SetFloatArray(const std::string& name, std::vector<float>& values);
	bool SetTexture(const std::string& name, gstd::ref_count_ptr<Texture> texture);

protected:
	gstd::ref_count_ptr<ShaderData> data_;

	// bool bLoadShader_;
	// IDirect3DVertexShader9* pVertexShader_;
	// IDirect3DPixelShader9* pPixelShader_;

	std::string technique_;
	std::map<std::string, gstd::ref_count_ptr<ShaderParameter>> mapParam_;

	ShaderData* _GetShaderData() { return data_.GetPointer(); }
	gstd::ref_count_ptr<ShaderParameter> _GetParameter(const std::string& name, bool bCreate);

	int _Begin();
	void _End();
	void _BeginPass(int pass = 0);
	void _EndPass();
	bool _SetupParameter();
};

} // namespace directx

#endif
