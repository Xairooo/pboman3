#pragma once

#include "deleteop.h"
#include "treewidgetbase.h"
#include "model/pbomodel2.h"
#include <QFutureWatcher>

namespace pboman3 {
    class TreeWidget : public TreeWidgetBase {
    Q_OBJECT
    public:
        struct ActionState {
            bool canOpen;
            bool canCopy;
            bool canCut;
            bool canPaste;
            bool canRemove;
            bool canRename;
        };

        explicit TreeWidget(QWidget* parent = nullptr);

        void selectionCopy();

        void selectionCut();

        void selectionPaste();

        void selectionRemove() const;

        void selectionRename() const;

        void setModel(PboModel2* model);

    signals:
        void backgroundOpStarted();

        void backgroundOpStopped();

        void actionStateChanged(const ActionState& state);

    protected:
        void dragStarted(const QList<PboNode*>& items) override;

        void dragDropped(PboNode* target, const QMimeData* mimeData) override;

    private:
        PboModel2* model_;
        DeleteOp delete_;
        QFutureWatcher<InteractionParcel> dragDropWatcher_;
        QFutureWatcher<InteractionParcel> cutCopyWatcher_;
        ActionState actionState_;

        void onSelectionChanged();

        QList<PboNode*> selectionCopyImpl();

        void dragStartExecute();

        void copyOrCutExecute();

        void addFilesFromPbo(PboNode* target, const QMimeData* mimeData);

        void addFilesFromFilesystem(const QList<QUrl>& urls);
    };
}
