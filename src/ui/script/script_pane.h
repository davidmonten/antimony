#ifndef SCRIPT_PANE_H
#define SCRIPT_PANE_H

#include <QPlainTextEdit>
#include "ui/script/editor.h"

namespace Ui { class MainWindow; }

class ScriptPane : public QWidget
{
    Q_OBJECT
public:
    ScriptPane(ScriptDatum* datum, QWidget* parent);

    /*
     *  Connect to appropriate UI actions and modify menus.
     */
    void customizeUI(Ui::MainWindow* ui);

    /*
     *  Override paint event so that we can style the widget with CSS.
     */
    void paintEvent(QPaintEvent* event) override;

protected slots:
    void onDatumChanged();

protected:
    ScriptDatum* d;

    ScriptEditor* editor;
    QPlainTextEdit* output;
    QPlainTextEdit* error;
};

#endif
