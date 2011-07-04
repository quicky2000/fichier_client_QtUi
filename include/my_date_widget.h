#ifndef MY_DATE_WIDGET
#define MY_DATE_WIDGET

#include <QWidget>
#include <QLineEdit>
#include <string>

class my_date_widget:public QLineEdit
{
  Q_OBJECT
 public:
  my_date_widget(QWidget * p_parent = NULL);
  const std::string get_iso_date(void)const;
  void set_iso_date(const std::string & p_iso_date);
  bool is_complete(void)const;
  bool is_empty(void)const;
  
  signals:
  void date_ok(void);

 private slots:
  void date_entered(void);
};

#endif
//EOF
