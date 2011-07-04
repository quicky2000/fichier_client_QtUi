#include "my_date_widget.h"

#include <QHBoxLayout>
#include <QIntValidator>
#include <QRegExpValidator>
#include <iostream>
#include <assert.h>

using namespace std;

my_date_widget::my_date_widget(QWidget * p_parent):
  QLineEdit(p_parent)
{
  setFixedSize(80,23);
  setInputMask("00/00/0000");
  connect(this,SIGNAL(editingFinished()), this, SLOT(date_entered(void)));
}

const std::string my_date_widget::get_iso_date(void)const
{
  string l_date =  text().toStdString();
  assert(l_date.length()==10);
  return l_date.substr(6,4)+"-"+l_date.substr(3,2)+"-"+l_date.substr(0,2);
}


void my_date_widget::set_iso_date(const std::string & p_iso_date)
{
  assert(p_iso_date.length()==10 || p_iso_date.length()==0);
  if(p_iso_date.length())
    {
      cout << "Iso date : \"" << p_iso_date << endl ;
      cout << "Day " << p_iso_date.substr(8,2) << endl ;
      cout << "Month " << p_iso_date.substr(5,2) << endl ;
      cout << "Year " << p_iso_date.substr(0,4) << endl ;
      setText((p_iso_date.substr(8,2)+"/"+p_iso_date.substr(5,2)+"/"+p_iso_date.substr(0,4)).c_str());
    }
  else
    {
      setText("");
    }
}

void my_date_widget::date_entered(void)
{
  string l_date =  text().toStdString();
  if(l_date.length()==10)
    {
      std::cout << "Date entered : \"" << l_date << "\"" << std::endl ;
      emit date_ok();
    }
  else
    {
    }
}

bool my_date_widget::is_complete(void)const
{
  return text().toStdString().length()==10;
}

bool my_date_widget::is_empty(void)const
{
  return text().toStdString()== "//";
}

#ifdef TOTO

my_date_widget::my_date_widget(QWidget * p_parent):
  QWidget(p_parent),
  m_day(NULL),
  m_month(NULL),
  m_year(NULL),
  m_date(NULL)
{
    QHBoxLayout *l_layout = new QHBoxLayout(this);
    // Part related to day
    l_layout->addWidget(new QLabel(tr("Jour :")));
    m_day = new QLineEdit("");
    m_day->setMaxLength(2);
    m_day->setFixedSize(28,23);
    m_day->setValidator(new QIntValidator(m_day));
    l_layout->addWidget(m_day);

    // Part related to month
    l_layout->addWidget(new QLabel(tr("Mois :")));
    m_month = new QLineEdit("");
    m_month->setMaxLength(2);
    m_month->setFixedSize(28,23);
    m_month->setValidator(new QIntValidator(m_month));
    l_layout->addWidget(m_month);

    // Part related to year
    l_layout->addWidget(new QLabel(tr("Annee :")));
    m_year = new QLineEdit("");
    m_year->setFixedSize(40,23);
    m_year->setMaxLength(4);
    m_year->setValidator(new QIntValidator(m_year));
    l_layout->addWidget(m_year);
    // Part related to date in a signle field
    l_layout->addWidget(new QLabel(tr("Date :")));
    m_date = new QLineEdit("");
    m_date->setFixedSize(80,23);
    //    m_date->setMaxLength(4);
    m_date->setInputMask("00/00/0000");
    l_layout->addWidget(m_date);
    
    cout << "SizeHint(" << m_date->sizeHint().width() << "," << m_date->sizeHint().height() << endl ;
}

const std::string my_date_widget::get_text(void)const
{
  cout << "Day : \"" << m_date->text().toStdString().substring(0,2);
  return m_year->text().toStdString() + m_month->text().toStdString() + m_day->text().toStdString();
}

#endif

//EOF
