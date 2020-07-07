#include "charts/custom_context.h"
#include <QLabel>
#include <QMessageBox>

//
CSimpleContext::CSimpleContext()
    : QDialog()
{
    m_gridLayout = new QGridLayout{this};

    m_gridLayout->addWidget(new QLabel(tr("Min")), 0, 1, 1, 1);
    m_gridLayout->addWidget(new QLabel(tr("Max")), 0, 2, 1, 1);
    m_gridLayout->addWidget(&m_minBord, 1, 1, 1, 1);
    m_gridLayout->addWidget(&m_maxBord, 1, 2, 1, 1);
    m_gridLayout->addWidget(&m_setButton, 2, 1, 1, 1);
	m_gridLayout->addWidget(&m_cancelButton, 2, 2, 1, 1);
	
    m_minBord.setMinimum(-1e9);
    m_minBord.setMaximum(1e9);
    m_minBord.setDecimals(4);
    m_minBord.setValue(-100);

    m_maxBord.setMinimum(-1e9);
    m_maxBord.setMaximum(1e9);
    m_maxBord.setDecimals(4);
    m_maxBord.setValue(100);

    m_setButton.setText(tr("Set range"));
	m_cancelButton.setText(tr("Cancel"));

    setVisible(false);
    connect(&m_setButton, &QPushButton::clicked, this, &CSimpleContext::onSetButtonClick);
	connect(&m_cancelButton, &QPushButton::clicked, this, &CSimpleContext::close);
	
	setWindowFlags(Qt ::WindowCloseButtonHint | Qt::WindowStaysOnTopHint );
}

CSimpleContext::~CSimpleContext()
{
    if (m_gridLayout)
	{
		delete m_gridLayout;
		m_gridLayout = nullptr;
	}
}

void CSimpleContext::onSetButtonClick()
{
    if (m_minBord.value() > m_maxBord.value())
    {
        QMessageBox::information(this, tr("Warning"), tr("Min value > max value"));
        return;
    }
    setVisible(false);
    emit onNewDataSet(m_minBord.value(), m_maxBord.value());
}

void CSimpleContext::onOffAutoscale()
{
	setVisible(false);
    if ( abs(m_maxBord.value() - m_minBord.value())>1e-6 )
		emit onNewDataSet(m_minBord.value(), m_maxBord.value());
}

void CSimpleContext::setValues(double min, double max)
{
    m_minBord.setValue(min);
	m_maxBord.setValue(max);
}
