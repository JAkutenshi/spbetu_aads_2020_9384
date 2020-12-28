#include "surfacegraph.h"

const int treeCount = 10;

SurfaceGraph::SurfaceGraph(Q3DSurface *surface) : m_graph(surface), m_uniform_distribution(false), m_normal_distribution(false), m_unbalanced_distribution(false){
    m_graph->axisX()->setRange(0.0f, 1.0f);
    m_graph->axisY()->setRange(0.0f, 1.0f);
    m_graph->axisZ()->setRange(0.0f, 1.0f);

    m_uniform_proxy = new QSurfaceDataProxy();
    m_uniform_series = new QSurface3DSeries(m_uniform_proxy);

    m_normal_proxy = new QSurfaceDataProxy();
    m_normal_series = new QSurface3DSeries(m_normal_proxy);

    m_unbalanced_proxy = new QSurfaceDataProxy();
    m_unbalanced_series = new QSurface3DSeries(m_unbalanced_proxy);

    m_tree_uniform = new Tree*[treeCount];
    m_tree_normal = new Tree*[treeCount];
    m_tree_unbalanced = new Tree*[treeCount];
    for(int i = 0; i < treeCount; i++){
        m_tree_uniform[i] = new Tree;
        m_tree_normal[i] = new Tree;
        m_tree_unbalanced[i] = new Tree;
    }
}

SurfaceGraph::~SurfaceGraph(){
    delete m_graph;
    for(int i = 0; i < treeCount; i++){
        delete m_tree_uniform[i];
        delete m_tree_normal[i];
        delete m_tree_unbalanced[i];
    }
    delete[] m_tree_uniform;
    delete[] m_tree_normal;
    delete[] m_tree_unbalanced;
}

void SurfaceGraph::fill_uniform_proxy(){
    double stepX = m_tree_uniform[treeCount - 1]->get_count() / (double)(m_tree_uniform[treeCount - 1]->get_count() - 1);
    double stepZ = m_tree_uniform[treeCount - 1]->get_count() / (double)(m_tree_uniform[treeCount - 1]->get_length() - 1);
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(treeCount);
    for (int i = 0 ; i < treeCount ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(treeCount);
        float x, y, z;
        if(m_tree_unbalanced[treeCount - 1]->get_count()){
            x = qMin((double)m_tree_unbalanced[treeCount - 1]->get_count(), m_tree_uniform[i]->get_count() * stepX);
        }
        else{
            x = qMin((double)m_tree_uniform[treeCount - 1]->get_count(), m_tree_uniform[i]->get_count() * stepX);
        }
        int index = 0;
        for(int j = 0; j < treeCount; j++){
            if(m_tree_unbalanced[treeCount - 1]->get_worst_time()){
                y = qMin(m_tree_unbalanced[treeCount - 1]->get_worst_time(), m_tree_uniform[i]->get_worst_time());
            }
            else{
                y = qMin(m_tree_uniform[treeCount - 1]->get_worst_time(), m_tree_uniform[i]->get_worst_time());
            }
            if(m_tree_unbalanced[treeCount - 1]->get_count()){
                z = qMin((double)m_tree_unbalanced[treeCount - 1]->get_count(), m_tree_uniform[i]->get_length() * stepZ);
            }
            else{
                z = qMin((double)m_tree_uniform[treeCount - 1]->get_count(), m_tree_uniform[i]->get_length() * stepZ);
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));;
        }
        *dataArray << newRow;
    }
    m_uniform_proxy->resetArray(dataArray);
}

void SurfaceGraph::fill_normal_proxy(){
    double stepX = m_tree_normal[treeCount - 1]->get_count() / (double)(m_tree_normal[treeCount - 1]->get_count() - 1);
    double stepZ = m_tree_normal[treeCount - 1]->get_count() / (double)(m_tree_normal[treeCount - 1]->get_length() - 1);
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(treeCount);
    for (int i = 0 ; i < treeCount ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(treeCount);
        float x, y, z;
        if(m_tree_unbalanced[treeCount - 1]->get_count()){
            x = qMin((double)m_tree_unbalanced[treeCount - 1]->get_count(), m_tree_normal[i]->get_count() * stepX);
        }
        else{
            x = qMin((double)m_tree_normal[treeCount - 1]->get_count(), m_tree_normal[i]->get_count() * stepX);
        }
        int index = 0;
        for(int j = 0; j < treeCount; j++){
            if(m_tree_unbalanced[treeCount - 1]->get_worst_time()){
                y = qMin(m_tree_unbalanced[treeCount - 1]->get_worst_time(), m_tree_normal[i]->get_worst_time());
            }
            else{
                y = qMin(m_tree_normal[treeCount - 1]->get_worst_time(), m_tree_normal[i]->get_worst_time());
            }
            if(m_tree_unbalanced[treeCount - 1]->get_count()){
                z = qMin((double)m_tree_unbalanced[treeCount - 1]->get_count(), m_tree_normal[i]->get_length() * stepZ);
            }
            else{
                z = qMin((double)m_tree_normal[treeCount - 1]->get_count(), m_tree_normal[i]->get_length() * stepZ);
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));;
        }
        *dataArray << newRow;
    }
    m_normal_proxy->resetArray(dataArray);
}

void SurfaceGraph::fill_unbalanced_proxy(){
    double stepX = m_tree_unbalanced[treeCount - 1]->get_count() / (double)(m_tree_unbalanced[treeCount - 1]->get_count() - 1);
    double stepZ = m_tree_unbalanced[treeCount - 1]->get_count() / (double)(m_tree_unbalanced[treeCount - 1]->get_length() - 1);
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(treeCount);
    for (int i = 0 ; i < treeCount ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(treeCount);
        float x = qMin((double)m_tree_unbalanced[treeCount - 1]->get_count(), m_tree_unbalanced[i]->get_count() * stepX);
        int index = 0;
        for(int j = 0; j < treeCount; j++){
            float y = qMin(m_tree_unbalanced[treeCount - 1]->get_worst_time(), m_tree_unbalanced[i]->get_worst_time());
            float z = qMin((double)m_tree_unbalanced[treeCount - 1]->get_count(), m_tree_unbalanced[i]->get_length() * stepZ);
            (*newRow)[index++].setPosition(QVector3D(x, y, z));;
        }
        *dataArray << newRow;
    }
    m_unbalanced_proxy->resetArray(dataArray);
}

void SurfaceGraph::enable_uniform_distribution(bool enable){
    if(enable){
        m_uniform_distribution = true;
        m_normal_distribution = false;
        m_unbalanced_distribution = false;

        m_normal_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_normal_series->setFlatShadingEnabled(true);

        m_graph->removeSeries(m_normal_series);
        m_graph->removeSeries(m_unbalanced_series);
        m_graph->addSeries(m_uniform_series);

        if(m_tree_unbalanced[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
        }
        else if(m_tree_uniform[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_uniform[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_uniform[treeCount - 1]->get_count());
        }
        if(m_tree_unbalanced[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_worst_time());
        }
        else if(m_tree_uniform[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_uniform[treeCount - 1]->get_worst_time());
        }
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);
    }
}

#include <iostream>

void SurfaceGraph::enable_normal_distributinon(bool enable){
    if(enable){
        m_uniform_distribution = false;
        m_normal_distribution = true;
        m_unbalanced_distribution = false;

        m_normal_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_normal_series->setFlatShadingEnabled(true);

        m_graph->removeSeries(m_uniform_series);
        m_graph->removeSeries(m_unbalanced_series);
        m_graph->addSeries(m_normal_series);

        if(m_tree_unbalanced[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
        }
        else if(m_tree_normal[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_normal[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_normal[treeCount - 1]->get_count());
        }
        if(m_tree_unbalanced[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_worst_time());
        }
        else if(m_tree_normal[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_normal[treeCount - 1]->get_worst_time());
        }
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);
    }
}

void SurfaceGraph::enable_unbalanced_distribution(bool enable){
    if(enable){
        m_uniform_distribution = false;
        m_normal_distribution = false;
        m_unbalanced_distribution = true;

        m_normal_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_normal_series->setFlatShadingEnabled(true);

        m_graph->removeSeries(m_uniform_series);
        m_graph->removeSeries(m_normal_series);
        m_graph->addSeries(m_unbalanced_series);

        if(m_tree_unbalanced[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
        }
        if(m_tree_unbalanced[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_worst_time());
        }
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);
    }
}

void SurfaceGraph::generate_new_tree(){
    if(m_uniform_distribution){
            for(int i = 0; i < treeCount; i++){
                m_tree_uniform[i]->reset(Distribution::UNIFORM);
                for(int j = 0; j < pow(2, i + 1) * treeCount; j++){
                    m_tree_uniform[i]->insert(j);
                }
                m_tree_uniform[i]->update_length();
                m_tree_uniform[i]->update_worst_time();
                std::cout << m_tree_uniform[i]->get_count() << " " << m_tree_uniform[i]->get_length() << std::endl;
            }
            fill_uniform_proxy();
            enable_uniform_distribution(true);
        }
    else if(m_normal_distribution){
        for(int i = 0; i < treeCount; i++){
            m_tree_normal[i]->reset(Distribution::NORMAL);
            for(int j = 0; j < pow(2, i + 1) * treeCount; j++){
                m_tree_normal[i]->insert(j);
            }
            m_tree_normal[i]->update_length();
            m_tree_normal[i]->update_worst_time();
            std::cout << m_tree_normal[i]->get_count() << " " << m_tree_normal[i]->get_length() << std::endl;
        }
        fill_normal_proxy();
        enable_normal_distributinon(true);
    }
    else if(m_unbalanced_distribution){
        for(int i = 0; i < treeCount; i++){
            m_tree_unbalanced[i]->reset(Distribution::UNBALANCED);
            for(int j = 0; j < pow(2, i + 1) * treeCount; j++){
                m_tree_unbalanced[i]->insert(j);
            }
            m_tree_unbalanced[i]->update_length();
            m_tree_unbalanced[i]->update_worst_time();
            std::cout << m_tree_unbalanced[i]->get_count() << " " << m_tree_unbalanced[i]->get_length() << std::endl;
        }
        fill_unbalanced_proxy();
        enable_unbalanced_distribution(true);
    }
}
