#ifndef GLDIRREGULARFORM_H
#define GLDIRREGULARFORM_H

#include "GLDMask_Global.h"

#include <QWidget>

class QPushButton;
class GLDCustomButton;

class GLDMASKSHARED_EXPORT GLDIrregularForm : public QWidget
{
    Q_OBJECT

public:
    explicit GLDIrregularForm(QWidget *parent = 0);
    explicit GLDIrregularForm(const QString & irregularImgPath, const QString & btnImgPath, QWidget *parent = nullptr);
    explicit GLDIrregularForm(const QString & irregularImgPath, QPushButton * btn, QWidget *parent = nullptr);

    ~GLDIrregularForm();

    /*
     * @brief 返回窗体的大小
     */
    QSize sizeHint() const;

    /**
    * @brief 设置标志和属性
    */
    void setFlagAndAttribute();

    /**
    * @brief 加载pixmap
    */
    void loadPixmap(const QString & pixmapPath);

    /**
    * @brief 设置pixmap
    */
    void setPixmap(const QPixmap & pm);

Q_SIGNALS:
    void irregularFormClicked();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QPushButton*     m_pPushBtn;        // 用户按钮
    GLDCustomButton* m_pCustomBtn;      // 自定义按钮
    QPixmap          m_irregularFormPm; // 需要显示提示信息的pixmap
};

#endif // GLDIRREGULARFORM_H
