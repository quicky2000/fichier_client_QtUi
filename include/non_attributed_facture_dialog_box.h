#ifndef _NON_ATTRIBUTED_FACTURE_DIALOG_BOX_H_
#define _NON_ATTRIBUTED_FACTURE_DIALOG_BOX_H_

#include <QDialog>
#include <vector>
#include "facture_status.h"

class QWidget;
class QLineEdit;
class my_date_widget;
class QPushButton;
class QComboBox;
class facture;

class non_attributed_facture_dialog_box: public QDialog
{
  Q_OBJECT
    public:
  non_attributed_facture_dialog_box(QWidget * p_parent,std::vector<facture_status> & p_status_list,facture & p_facture);

  public slots:
  void accept(void);
  void reject(void);

 private:
  facture & m_facture;
  QLineEdit * m_facture_reference_field;
  my_date_widget * m_date_field;
  QPushButton * m_ok_button;
  QPushButton * m_cancel_button;
  QComboBox * m_status_field;
  std::vector<uint32_t> m_status_ids;
};

#endif

