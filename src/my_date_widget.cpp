#include "my_date_widget.h"
#include "fichier_client_QtUi_utils.h"

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
  return fichier_client_QtUi_utils::get_iso_date(text().toStdString());
}


void my_date_widget::set_iso_date(const std::string & p_iso_date)
{

  setText(fichier_client_QtUi_utils::get_human_date(p_iso_date).c_str());
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


//EOF
