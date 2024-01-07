#include <iostream>
#include <Urlmon.h>
#include <fstream>
#include <Windows.h>

class DownloadProgress : public IBindStatusCallback {
public:
    HRESULT __stdcall QueryInterface(const IID&, void**) {
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef(void) {
        return 1;
    }
    ULONG STDMETHODCALLTYPE Release(void) {
        return 1;
    }
    HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib) {
        return E_NOTIMPL;
    }
    virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG* pnPriority) {
        return E_NOTIMPL;
    }
    virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) {
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) {
        return E_NOTIMPL;
    }
    virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) {
        return E_NOTIMPL;
    }
    virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) {
        return E_NOTIMPL;
    }
    virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk) {
        return E_NOTIMPL;
    }

    virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
    {
        std::wcout << ulProgress << " of " << ulProgressMax << '\n';
        return S_OK;
    }
};

int main() {
    DownloadProgress downloadStatus;

    URLDownloadToFile(NULL, L"https://github.com/Denellyne/PCXSense/releases/download/Latest/PCXSense.rar", L"PCXSense.rar", 0, static_cast<IBindStatusCallback*>(&downloadStatus));
    system("unrar x -o+ PCXSense.rar");
    DeleteFile(L"PCXSense.rar");
    system("PCXSense.exe");

    return 0;
}