#ifndef _NON_ATTRIBUTED_FACTURE_WIDGET_H_
#define _NON_ATTRIBUTED_FACTURE_WIDGET_H_

#include "base_facture_widget.h"
#include "facture_reason.h"
#include <vector>

class non_attributed_facture_widget:
public base_facture_widget
{
  Q_OBJECT
    public:
  non_attributed_facture_widget(QWidget * p_parent);

  void set_enabled(bool p_enabled);

  const facture_reason * get_facture_reason(void)const;
  void set_reason_list(const std::vector<facture_reason> & p_reason_list);

 signals:
  void reason_selected(void);

  private slots:
  void treat_reason_selected_event(int);

 private:
  QComboBox * m_reason_field;
  std::vector<facture_reason> m_reasons;

};

#endif
