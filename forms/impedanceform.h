/**
@file impedanceform.h

@brief Объявление класса окна информации о импедансе

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef IMPEDANCEFORM_H
#define IMPEDANCEFORM_H
//----------------------------------------------------------------------------------
#include <QMainWindow>
#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
namespace Ui
{
	class ImpedanceForm;
}
//----------------------------------------------------------------------------------
class ImpedanceForm : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImpedanceForm(QWidget *parent = nullptr);
	~ImpedanceForm();

	void resetValues();

public slots:
	void OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData);

private:
	Ui::ImpedanceForm *ui;
};
//----------------------------------------------------------------------------------
#endif // IMPEDANCEFORM_H
//----------------------------------------------------------------------------------
