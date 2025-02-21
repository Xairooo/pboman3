#include <gtest/gtest.h>
#include <filesystem>
#include "dllmain_test.h"
#include "registry.h"

namespace pboman3::test {
    TEST(DllRegisterServerTest, RegistersEntryInRegistry) {
        const HRESULT hr = DllRegisterServer();
        ASSERT_TRUE(SUCCEEDED(hr));

        const string path = Registry::getExecutablePath();
        ASSERT_FALSE(path.empty());
    }

    TEST(DllUnregisterServerTest, UnregistersEntryInRegistry) {
        const HRESULT hr = DllUnregisterServer();
        ASSERT_TRUE(SUCCEEDED(hr));
    }

    // TEST(DrawIconTest, IconDraws) {
    //     const string exePath = Registry::getExecutablePath();
    //
    //     HICON icon;
    //     ExtractIconEx(exePath.data(), 0, NULL, &icon, 1);
    //
    //     HDC dc = GetDC(NULL);
    //     HBITMAP bitmap = CreateCompatibleBitmap(dc, 16, 16);
    //     HGDIOBJ prev = SelectObject(dc, bitmap);
    //
    //     BOOL ok = DrawIcon(dc, 0, 0, icon);
    //
    //     DestroyIcon(icon);
    //     DeleteObject(bitmap);
    //     DeleteDC(dc);
    // }

    TEST(DllRegisterServerTest, RegistersDevelopmentApplication) {
        using namespace std::filesystem;

        path binaryDir(BINARY_DIR);
        binaryDir = binaryDir.lexically_normal();
        const string exe = binaryDir.parent_path().append("pbom").append("pbom.exe").string();
        const string dll = binaryDir.append("pboe.dll").string();

        const HRESULT hr = Registry::registerServer(exe, dll);
        ASSERT_TRUE(SUCCEEDED(hr));

        const string path = Registry::getExecutablePath();
        ASSERT_FALSE(path.empty());
    }

    TEST(DllRegisterServerTest, UnregistersDevelopmentApplication) {
        const HRESULT hr = Registry::unregisterServer();
        ASSERT_TRUE(SUCCEEDED(hr));
    }
}
