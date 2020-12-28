#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtWidgets>
#include <QtDataVisualization/Q3DSurface>

#include "tree.h"

using namespace QtDataVisualization;

class SurfaceGraph : public QObject{
    Q_OBJECT
public:
    SurfaceGraph(Q3DSurface *surface);
    ~SurfaceGraph();

    void enable_uniform_distribution(bool enable);
    void enable_normal_distributinon(bool enable);
    void enable_unbalanced_distribution(bool enable);
    void generate_new_tree();

private:
    void fill_uniform_proxy();
    void fill_normal_proxy();
    void fill_unbalanced_proxy();

private:
    Q3DSurface *m_graph;

    QSurfaceDataProxy *m_uniform_proxy;
    QSurface3DSeries *m_uniform_series;
    bool m_uniform_distribution;

    QSurfaceDataProxy *m_normal_proxy;
    QSurface3DSeries *m_normal_series;
    bool m_normal_distribution;

    QSurfaceDataProxy *m_unbalanced_proxy;
    QSurface3DSeries *m_unbalanced_series;
    bool m_unbalanced_distribution;

    Tree **m_tree_uniform;
    Tree **m_tree_normal;
    Tree **m_tree_unbalanced;
};

#endif // SURFACEGRAPH_H
