#include "postal_code_widget.h"

//------------------------------------------------------------------------------
postal_code_widget::postal_code_widget(QWidget * p_parent):
  QLineEdit(p_parent)
{
  this->setInputMask("00000");
  this->setFixedSize(50,23);
}

//------------------------------------------------------------------------------
bool postal_code_widget::is_complete(void)const
{
  return this->text().toStdString().size() == 5;
}

//------------------------------------------------------------------------------
bool postal_code_widget::is_empty(void)const
{
  return this->text().toStdString()=="";
}
//EOF
