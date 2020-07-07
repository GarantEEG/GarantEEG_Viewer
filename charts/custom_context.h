#ifndef CUSTOM_CONTEXT_H
#define CUSTOM_CONTEXT_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGridLayout>

// context menu set border
class CSimpleContext : public QDialog
{
    Q_OBJECT
public:
    CSimpleContext();
    ~CSimpleContext();

public:
    void onSetButtonClick();
    void onOffAutoscale();
    void setValues(double min, double max);
    double getMin() { return m_minBord.value(); }
	double getMax() { return m_maxBord.value(); }

signals : void onNewDataSet(double min, double max);

private:
    QGridLayout *m_gridLayout{nullptr};
    QPushButton m_setButton;
    QPushButton m_cancelButton;
    QDoubleSpinBox m_minBord;
    QDoubleSpinBox m_maxBord;
};

#endif // CUSTOM_CONTEXT_H
