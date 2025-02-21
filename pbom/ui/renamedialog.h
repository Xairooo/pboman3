#pragma once

#include <QDialog>
#include "model/pbonode.h"
#include "ui_renamedialog.h"

namespace pboman3 {
    class RenameDialog : public QDialog {
    Q_OBJECT

    public:
        RenameDialog(QWidget* parent, PboNode* node);

        ~RenameDialog() override;
       
    public slots:
        void onTextEdited(const QString& title) const;

        void accept() override;

    private:
        Ui::RenameDialog* ui_;
        PboNode* node_;
        bool isDirty_;

        bool setErrorState(const TitleError& err) const;

        void disableAccept(bool disable) const;

        void setTextAndSelect() const;
    };
}
