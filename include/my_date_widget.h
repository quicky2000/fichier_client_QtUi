#ifndef MY_DATE_WIDGET
#define MY_DATE_WIDGET

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <string>

#ifdef TOTO
class my_date_widget:public QWidget
{
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
