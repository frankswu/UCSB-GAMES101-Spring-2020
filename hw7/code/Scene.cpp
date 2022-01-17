//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here

    Intersection intersection = intersect(ray);

    if (!intersection.happened) {
        return Vector3f(0.0f);
    }

    // (1) 直接看到光源
    if (intersection.obj->hasEmit()) {
        return Vector3f(1.0f);
    }

    // (2) L_dir: 光源照射到物体一次反射到眼中
    // (3) L_indir: 光源经过多次反射照射到物体再反射到眼中

    auto p = intersection.coords;
    auto wo = -ray.direction;
    auto N = intersection.normal;

    Intersection inter;
    float pdf_light;
    sampleLight(inter, pdf_light);

    auto x = inter.coords;
    auto ws = normalize(x - p);
    auto NN = inter.normal;
    auto emit = inter.emit;
    auto L_dir = Vector3f();

    Intersection hit1 = intersect(Ray(p, ws));
    auto eps = 1e-3;
    if ((x - hit1.coords).norm() <= eps) {
        L_dir = emit * intersection.m->eval(ws, wo, N) * dotProduct(ws, N) * dotProduct(-ws, NN) / (hit1.distance * hit1.distance) / pdf_light;
    }

    auto L_indir = Vector3f();
    if (get_random_float() <= RussianRoulette) {
        auto wi = intersection.m->sample(wo, N);
        Intersection hit2 = intersect(Ray(p, wi)); 
        auto q = hit2.coords;
        if (hit2.happened && !hit2.obj->hasEmit()) {
            L_indir = castRay(Ray(q, wi), depth+1) * hit2.m->eval(wo, wi, N) * dotProduct(wi, N) / hit2.m->pdf(wo, wi, N) / RussianRoulette;
        }     
    }

    return L_dir + L_indir;
}