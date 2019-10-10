#ifndef __DIRECTX_METASEQUOIAMESH__
#define __DIRECTX_METASEQUOIAMESH__

#include "RenderObject.hpp"

namespace directx {

/**********************************************************
//MetasequoiaMesh
**********************************************************/
class MetasequoiaMesh;
class MetasequoiaMeshData : public DxMeshData {
	friend MetasequoiaMesh;

public:
	MetasequoiaMeshData();
	~MetasequoiaMeshData() override;
	bool CreateFromFileReader(gstd::ref_count_ptr<gstd::FileReader> reader) override;

	class Material;
	class Object;
	class RenderObject;

protected:
	std::wstring path_;
	std::vector<gstd::ref_count_ptr<Material>> material_;
	std::vector<gstd::ref_count_ptr<RenderObject>> obj_;

	void _ReadMaterial(gstd::Scanner& scanner);
	void _ReadObject(gstd::Scanner& scanner);

private:
	struct NormalData {
		std::vector<int> listIndex_;
		D3DXVECTOR3 normal_;
		virtual ~NormalData() {}
	};
};

class MetasequoiaMeshData::Material {
	friend MetasequoiaMeshData;
	friend MetasequoiaMeshData::RenderObject;

public:
	Material() { ZeroMemory(&mat_, sizeof(D3DMATERIAL9)); };
	virtual ~Material() = default;

protected:
	std::wstring name_; //材質名
	D3DMATERIAL9 mat_;
	gstd::ref_count_ptr<Texture> texture_; //模様マッピング 相対パス
	std::string pathTextureAlpha_; //透明マッピングの名前 相対パス(未使用)
	std::string pathTextureBump_; //凹凸マッピングの名前 相対パス(未使用)
};

class MetasequoiaMeshData::Object {
	friend MetasequoiaMeshData;

public:
	Object() = default;
	virtual ~Object() = default;

protected:
	struct Face {
		//面の頂点
		struct Vertex {
			long indexVertex_; //頂点のインデックス
			D3DXVECTOR2 tcoord_; //テクスチャの座標
		};
		long indexMaterial_; //マテリアルのインデックス
		std::vector<Vertex> vertices_; //面の頂点
		Face() { indexMaterial_ = -1; }
	};
	bool bVisible_;
	std::wstring name_; //オブジェクト名
	std::vector<D3DXVECTOR3> vertices_; //頂点たち
	std::vector<Face> faces_; //面たち
};

class MetasequoiaMeshData::RenderObject : public RenderObjectNX {
	friend MetasequoiaMeshData;

public:
	RenderObject() = default;
	~RenderObject() override = default;
	void Render() override;

protected:
	gstd::ref_count_ptr<Material> material_;
};

class MetasequoiaMesh : public DxMesh {
protected:
public:
	MetasequoiaMesh() = default;
	~MetasequoiaMesh() override = default;
	bool CreateFromFileReader(gstd::ref_count_ptr<gstd::FileReader> reader) override;
	bool CreateFromFileInLoadThread(const std::wstring& path) override;
	std::wstring GetPath() override;
	void Render() override;

	std::vector<DxTriangle> CreateIntersectionTriangles();
};

} // namespace directx

#endif
