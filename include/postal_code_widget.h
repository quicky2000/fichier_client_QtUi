#ifndef POSTAL_CODE_WIDGET
#define POSTAL_CODE_WIDGET

#include <QLineEdit>

class postal_code_widget:public QLineEdit
{
 public:
  postal_code_widget(QWidget * p_parent = NULL);
  bool is_complete(void)const;
  bool is_empty(void)const;
};

#endif
//EOF
