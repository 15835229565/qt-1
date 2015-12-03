#ifndef GLDPAPERTABLEVIEW_P_H
#define GLDPAPERTABLEVIEW_P_H

#include "GLDTableView_p.h"
#include "GLDPaperTableView.h"

class GlodonPaperTableViewPrivate : public GlodonTableViewPrivate
{
    Q_DECLARE_PUBLIC(GlodonPaperTableView)

public:
    GlodonPaperTableViewPrivate() :
        m_paperState(GlodonHeaderView::Press)
    {

    }

public:
    GlodonHeaderView::ResizeState m_paperState;  //�ڷֲ�ģʽ�¼�¼��
};
#endif // GLDPAPERTABLEVIEW_P_H
