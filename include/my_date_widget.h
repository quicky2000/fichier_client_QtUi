#ifndef MY_DATE_WIDGET
#define MY_DATE_WIDGET

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <string>

class my_date_widget:public QWidget
{
  Q_OBJECT
 public:
  my_date_widget(QWidget * p_parent = NULL);
  const std::string get_text(void)const;
 private:
  QLineEdit *m_day;
  QLineEdit *m_month;
  QLineEdit *m_year;
  QLineEdit *m_date;
};
#endif
//EOF
