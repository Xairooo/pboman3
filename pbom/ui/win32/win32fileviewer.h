#pragma once

#include "ui/fileviewer.h"
#include "util/appexception.h"

namespace pboman3 {
    class Win32FileViewerException : public AppException {
    public:
        Win32FileViewerException(QString message);

        friend QDebug operator<<(QDebug debug, const Win32FileViewerException& ex);

        void raise() const override;

        QException* clone() const override;
    };

    class Win32FileViewer : public FileViewer {
    public:
        void previewFile(const QString& path) override;
    };
}
