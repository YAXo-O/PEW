#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>

class Renderer : public QObject
{
    Q_OBJECT
public:
    explicit Renderer(QObject *parent = nullptr);
    virtual ~Renderer() {}

public slots:
    virtual void start() {}
    virtual void stop() {}
    virtual void pause() {}

signals:
    void finished();
};

#endif // RENDERER_H
