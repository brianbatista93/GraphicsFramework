#include "DX11Device.h"
#include "DX11Resources.h"

bool
DX11Device::LoadPreCompiledShader(const std::filesystem::path& filename, void** data, uint64* size)
{
    auto realFilename = m_shaderDir / filename;
    if (!std::filesystem::exists(realFilename)) {
        return false;
    }

    CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {};
    extendedParams.dwSize                          = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    extendedParams.dwFileAttributes                = FILE_ATTRIBUTE_NORMAL;
    extendedParams.dwFileFlags                     = FILE_FLAG_SEQUENTIAL_SCAN;
    extendedParams.dwSecurityQosFlags              = SECURITY_ANONYMOUS;
    extendedParams.lpSecurityAttributes            = nullptr;
    extendedParams.hTemplateFile                   = nullptr;

    Wrappers::FileHandle file(CreateFile2(realFilename.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, &extendedParams));

    if (file.Get() == INVALID_HANDLE_VALUE) {
        return false;
    }

    FILE_STANDARD_INFO fileInfo = {};
    if (!GetFileInformationByHandleEx(file.Get(), FileStandardInfo, &fileInfo, sizeof(fileInfo))) {
        return false;
    }

    if (fileInfo.EndOfFile.HighPart != 0) {
        return false;
    }

    *data = reinterpret_cast<byte*>(malloc(fileInfo.EndOfFile.LowPart));
    *size = fileInfo.EndOfFile.LowPart;

    if (!ReadFile(file.Get(), *data, fileInfo.EndOfFile.LowPart, nullptr, nullptr)) {
        return false;
    }

    return true;
}

GpuVertexShader*
DX11Device::CreateVertexShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11VertexShader* vshader = nullptr;

    if (FAILED(m_d3d11Device->CreateVertexShader(data, size, nullptr, &vshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuVertexShader* result = new DX11VertexShader(vshader, data, size);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuPixelShader*
DX11Device::CreatePixelShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11PixelShader* pshader = nullptr;

    if (FAILED(m_d3d11Device->CreatePixelShader(data, size, nullptr, &pshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuPixelShader* result = new DX11PixelShader(pshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuDomainShader*
DX11Device::CreateDomainShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11DomainShader* dshader = nullptr;

    if (FAILED(m_d3d11Device->CreateDomainShader(data, size, nullptr, &dshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuDomainShader* result = new DX11DomainShader(dshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuHullShader*
DX11Device::CreateHullShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11HullShader* hshader = nullptr;

    if (FAILED(m_d3d11Device->CreateHullShader(data, size, nullptr, &hshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuHullShader* result = new DX11HullShader(hshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuGeometryShader*
DX11Device::CreateGeometryShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11GeometryShader* gshader = nullptr;

    if (FAILED(m_d3d11Device->CreateGeometryShader(data, size, nullptr, &gshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuGeometryShader* result = new DX11GeometryShader(gshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuComputeShader*
DX11Device::CreateComputeShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11ComputeShader* cshader = nullptr;

    if (FAILED(m_d3d11Device->CreateComputeShader(data, size, nullptr, &cshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuComputeShader* result = new DX11ComputeShader(cshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}