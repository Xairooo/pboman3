#include "win32iconmgr.h"
#include <QPixmap>
#include <QImage>
#include "util/appexception.h"
#include <Windows.h>
#include <shellapi.h>

namespace pboman3 {
    Win32IconMgr::Win32IconMgr() {
        cache_[""] = QIcon(":ifile.png");
        cache_[":folder-closed:"] = QIcon(":ifolderclosed.png");
        cache_[":folder-opened:"] = QIcon(":ifolderopened.png");
    }

    const QIcon& Win32IconMgr::getIconForExtension(const QString& extension) {
        if (extension.startsWith("."))
            throw AppException("The extension must not start with a \".\" symbol");

        if (cache_.contains(extension)) {
            return cache_[extension];
        }

        SHFILEINFOW info;
        const QString fn = "file." + extension;
        const HRESULT hr = SHGetFileInfoW(
            reinterpret_cast<LPCWSTR>(fn.utf16()),
            FILE_ATTRIBUTE_NORMAL,
            &info,
            sizeof info,
            SHGFI_ICON | SHGFI_USEFILEATTRIBUTES);

        if (SUCCEEDED(hr)) {
            cache_[extension] = QIcon(QPixmap::fromImage(QImage::fromHICON(info.hIcon)));
            DestroyIcon(info.hIcon);
            return cache_[extension];
        }

        return cache_[""];
    }

    const QIcon& Win32IconMgr::getFolderOpenedIcon() {
        return cache_[":folder-opened:"];
    }

    const QIcon& Win32IconMgr::getFolderClosedIcon() {
        return cache_[":folder-closed:"];
    }
}
