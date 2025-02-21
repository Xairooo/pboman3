#include "pboheaderio.h"
#include "pbodatastream.h"

namespace pboman3 {
    using namespace std;

    PboHeaderIO::PboHeaderIO(PboFile* file)
        : file_(file) {
    }

    QSharedPointer<PboEntry> PboHeaderIO::readNextEntry() const {
        PboDataStream data(file_);

        try {
            QString fileName;
            data >> fileName;

            PboPackingMethod packingMethod;
            data >> packingMethod;

            qint32 originalSize;
            data >> originalSize;

            qint32 reserved;
            data >> reserved;

            qint32 timeStamp;
            data >> timeStamp;

            qint32 dataSize;
            data >> dataSize;

            return QSharedPointer<PboEntry>(new PboEntry(fileName, packingMethod, originalSize, reserved, timeStamp, dataSize));
        } catch (PboEofException&) {
            return nullptr;
        }
    }

    QSharedPointer<PboHeader> PboHeaderIO::readNextHeader() const {
        PboDataStream data(file_);

        try {
            QString name;
            data >> name;

            if (name.isEmpty())
                return QSharedPointer<PboHeader>(new PboHeader("", ""));

            QString value;
            data >> value;

            return QSharedPointer<PboHeader>(new PboHeader(name, value));
        } catch (PboEofException&) {
            return nullptr;
        }
    }

    void PboHeaderIO::writeEntry(const PboEntry& entry) const {
        PboDataStream data(file_);

        data << entry.fileName();
        data << entry.packingMethod();
        data << entry.originalSize();
        data << entry.reserved();
        data << entry.timestamp();
        data << entry.dataSize();
    }

    void PboHeaderIO::writeHeader(const PboHeader& header) const {
        PboDataStream data(file_);

        if (header.isBoundary()) {
            data << static_cast<quint8>(0);
        } else {
            data << header.name;
            data << header.value;
        }
    }

}
