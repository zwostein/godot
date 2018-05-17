/*************************************************************************/
/*  atmosphere.cpp                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "atmosphere.h"
#include "servers/visual_server.h"

void Atmosphere::set_num_out_scatter(unsigned int p_num_out_scatter) {

	num_out_scatter = p_num_out_scatter;
	VS::get_singleton()->atmosphere_set_num_out_scatter(atmosphere, p_num_out_scatter);
}

unsigned int Atmosphere::get_num_out_scatter() const {

	return num_out_scatter;
}

void Atmosphere::set_num_in_scatter(unsigned int p_num_in_scatter) {

	num_in_scatter = p_num_in_scatter;
	VS::get_singleton()->atmosphere_set_num_in_scatter(atmosphere, p_num_in_scatter);
}

unsigned int Atmosphere::get_num_in_scatter() const {

	return num_in_scatter;
}

void Atmosphere::set_inner_radius(float p_inner_radius) {

	inner_radius = p_inner_radius;
	VS::get_singleton()->atmosphere_set_inner_radius(atmosphere, p_inner_radius);
	_change_notify("inner_radius");
	update_gizmo();}

float Atmosphere::get_inner_radius() const {

	return inner_radius;
}

void Atmosphere::set_surface_radius(float p_surface_radius) {

	surface_radius = p_surface_radius;
	VS::get_singleton()->atmosphere_set_surface_radius(atmosphere, p_surface_radius);
	_change_notify("surface_radius");
	update_gizmo();
}

float Atmosphere::get_surface_radius() const {

	return surface_radius;
}

void Atmosphere::set_surface_margin(float p_surface_margin) {

	surface_margin = p_surface_margin;
	VS::get_singleton()->atmosphere_set_surface_margin(atmosphere, p_surface_margin);
}

float Atmosphere::get_surface_margin() const {

	return surface_margin;
}

void Atmosphere::set_outer_radius(float p_outer_radius) {

	outer_radius = p_outer_radius;
	VS::get_singleton()->atmosphere_set_outer_radius(atmosphere, p_outer_radius);
	_change_notify("outer_radius");
	update_gizmo();
}

float Atmosphere::get_outer_radius() const {

	return outer_radius;
}

void Atmosphere::set_ph_ray(float p_ph_ray) {

	ph_ray = p_ph_ray;
	VS::get_singleton()->atmosphere_set_ph_ray(atmosphere, p_ph_ray);
}

float Atmosphere::get_ph_ray() const {

	return ph_ray;
}

void Atmosphere::set_ph_mie(float p_ph_mie) {

	ph_mie = p_ph_mie;
	VS::get_singleton()->atmosphere_set_ph_mie(atmosphere, p_ph_mie);
}

float Atmosphere::get_ph_mie() const {

	return ph_mie;
}

void Atmosphere::set_k_ray(const Vector3 & p_k_ray) {

	k_ray = p_k_ray;
	VS::get_singleton()->atmosphere_set_k_ray(atmosphere, p_k_ray);
}

Vector3 Atmosphere::get_k_ray() const {

	return k_ray;
}

void Atmosphere::set_k_mie(const Vector3 & p_k_mie) {

	k_mie = p_k_mie;
	VS::get_singleton()->atmosphere_set_k_mie(atmosphere, p_k_mie);
}

Vector3 Atmosphere::get_k_mie() const {

	return k_mie;
}

void Atmosphere::set_k_mie_ex(float p_k_mie_ex) {

	k_mie_ex = p_k_mie_ex;
	VS::get_singleton()->atmosphere_set_k_mie_ex(atmosphere, p_k_mie_ex);
}

float Atmosphere::get_k_mie_ex() const {

	return k_mie_ex;
}

void Atmosphere::set_g_mie(float p_g_mie) {

	g_mie = p_g_mie;
	VS::get_singleton()->atmosphere_set_g_mie(atmosphere, p_g_mie);
}

float Atmosphere::get_g_mie() const {

	return g_mie;
}

void Atmosphere::set_intensity(float p_intensity) {

	intensity = p_intensity;
	VS::get_singleton()->atmosphere_set_intensity(atmosphere, p_intensity);
}

float Atmosphere::get_intensity() const {

	return intensity;
}

void Atmosphere::set_direct_irradiance_attenuation(float p_attenuation) {

	direct_irradiance_attenuation = p_attenuation;
	VS::get_singleton()->atmosphere_set_direct_irradiance_attenuation(atmosphere, p_attenuation);
}

float Atmosphere::get_direct_irradiance_attenuation() const {

	return direct_irradiance_attenuation;
}

void Atmosphere::set_indirect_irradiance_intensity(float p_intensity) {

	indirect_irradiance_intensity = p_intensity;
	VS::get_singleton()->atmosphere_set_indirect_irradiance_intensity(atmosphere, p_intensity);
}

float Atmosphere::get_indirect_irradiance_intensity() const {

	return indirect_irradiance_intensity;
}

void Atmosphere::set_enable_shadows(bool p_enable) {

	enable_shadows = p_enable;
	VS::get_singleton()->atmosphere_set_enable_shadows(atmosphere, p_enable);
}

bool Atmosphere::are_shadows_enabled() const {

	return enable_shadows;
}

void Atmosphere::set_shadow_bias(float p_bias) {

	shadow_bias = p_bias;
	VS::get_singleton()->atmosphere_set_shadow_bias(atmosphere, p_bias);
}

float Atmosphere::get_shadow_bias() const {

	return shadow_bias;
}


AABB Atmosphere::get_aabb() const {

	AABB aabb;
	aabb.position = Vector3(-outer_radius, -outer_radius, -outer_radius);
	aabb.size = Vector3(outer_radius*2.0, outer_radius*2.0, outer_radius*2.0);
	return aabb;
}

PoolVector<Face3> Atmosphere::get_faces(uint32_t p_usage_flags) const {

	return PoolVector<Face3>();
}

void Atmosphere::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_num_out_scatter", "num_out_scatter"), &Atmosphere::set_num_out_scatter);
	ClassDB::bind_method(D_METHOD("get_num_out_scatter"), &Atmosphere::get_num_out_scatter);

	ClassDB::bind_method(D_METHOD("set_num_in_scatter", "num_in_scatter"), &Atmosphere::set_num_in_scatter);
	ClassDB::bind_method(D_METHOD("get_num_in_scatter"), &Atmosphere::get_num_in_scatter);

	ClassDB::bind_method(D_METHOD("set_inner_radius", "inner_radius"), &Atmosphere::set_inner_radius);
	ClassDB::bind_method(D_METHOD("get_inner_radius"), &Atmosphere::get_inner_radius);

	ClassDB::bind_method(D_METHOD("set_surface_radius", "surface_radius"), &Atmosphere::set_surface_radius);
	ClassDB::bind_method(D_METHOD("get_surface_radius"), &Atmosphere::get_surface_radius);

	ClassDB::bind_method(D_METHOD("set_surface_margin", "surface_margin"), &Atmosphere::set_surface_margin);
	ClassDB::bind_method(D_METHOD("get_surface_margin"), &Atmosphere::get_surface_margin);

	ClassDB::bind_method(D_METHOD("set_outer_radius", "outer_radius"), &Atmosphere::set_outer_radius);
	ClassDB::bind_method(D_METHOD("get_outer_radius"), &Atmosphere::get_outer_radius);

	ClassDB::bind_method(D_METHOD("set_ph_ray", "ph_ray"), &Atmosphere::set_ph_ray);
	ClassDB::bind_method(D_METHOD("get_ph_ray"), &Atmosphere::get_ph_ray);

	ClassDB::bind_method(D_METHOD("set_ph_mie", "ph_mie"), &Atmosphere::set_ph_mie);
	ClassDB::bind_method(D_METHOD("get_ph_mie"), &Atmosphere::get_ph_mie);

	ClassDB::bind_method(D_METHOD("set_k_ray", "k_ray"), &Atmosphere::set_k_ray);
	ClassDB::bind_method(D_METHOD("get_k_ray"), &Atmosphere::get_k_ray);

	ClassDB::bind_method(D_METHOD("set_k_mie", "k_mie"), &Atmosphere::set_k_mie);
	ClassDB::bind_method(D_METHOD("get_k_mie"), &Atmosphere::get_k_mie);

	ClassDB::bind_method(D_METHOD("set_k_mie_ex", "k_mie_ex"), &Atmosphere::set_k_mie_ex);
	ClassDB::bind_method(D_METHOD("get_k_mie_ex"), &Atmosphere::get_k_mie_ex);

	ClassDB::bind_method(D_METHOD("set_g_mie", "g_mie"), &Atmosphere::set_g_mie);
	ClassDB::bind_method(D_METHOD("get_g_mie"), &Atmosphere::get_g_mie);

	ClassDB::bind_method(D_METHOD("set_intensity", "intensity"), &Atmosphere::set_intensity);
	ClassDB::bind_method(D_METHOD("get_intensity"), &Atmosphere::get_intensity);

	ClassDB::bind_method(D_METHOD("set_direct_irradiance_attenuation", "attenuation"), &Atmosphere::set_direct_irradiance_attenuation);
	ClassDB::bind_method(D_METHOD("get_direct_irradiance_attenuation"), &Atmosphere::get_direct_irradiance_attenuation);

	ClassDB::bind_method(D_METHOD("set_indirect_irradiance_intensity", "intensity"), &Atmosphere::set_indirect_irradiance_intensity);
	ClassDB::bind_method(D_METHOD("get_indirect_irradiance_intensity"), &Atmosphere::get_indirect_irradiance_intensity);

	ClassDB::bind_method(D_METHOD("set_enable_shadows", "enable"), &Atmosphere::set_enable_shadows);
	ClassDB::bind_method(D_METHOD("are_shadows_enabled"), &Atmosphere::are_shadows_enabled);

	ClassDB::bind_method(D_METHOD("set_shadow_bias", "bias"), &Atmosphere::set_shadow_bias);
	ClassDB::bind_method(D_METHOD("get_shadow_bias"), &Atmosphere::get_shadow_bias);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_out_scatter", PROPERTY_HINT_RANGE, "0,128,1"), "set_num_out_scatter", "get_num_out_scatter");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_in_scatter", PROPERTY_HINT_RANGE, "0,256,1"), "set_num_in_scatter", "get_num_in_scatter");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "inner_radius"), "set_inner_radius", "get_inner_radius");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "surface_radius"), "set_surface_radius", "get_surface_radius");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "surface_margin"), "set_surface_margin", "get_surface_margin");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "outer_radius"), "set_outer_radius", "get_outer_radius");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "ph_ray"), "set_ph_ray", "get_ph_ray");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "ph_mie"), "set_ph_mie", "get_ph_mie");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "k_ray"), "set_k_ray", "get_k_ray");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "k_mie"), "set_k_mie", "get_k_mie");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "k_mie_ex"), "set_k_mie_ex", "get_k_mie_ex");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "g_mie", PROPERTY_HINT_RANGE, "-0.99,0.99,0.01"), "set_g_mie", "get_g_mie");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "intensity", PROPERTY_HINT_RANGE, "0,16,0.1"), "set_intensity", "get_intensity");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "direct_irradiance_attenuation", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_direct_irradiance_attenuation", "get_direct_irradiance_attenuation");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "indirect_irradiance_intensity", PROPERTY_HINT_RANGE, "0,16,0.01"), "set_indirect_irradiance_intensity", "get_indirect_irradiance_intensity");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_shadows"), "set_enable_shadows", "are_shadows_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "shadow_bias"), "set_shadow_bias", "get_shadow_bias");
}

Atmosphere::Atmosphere() {

	num_out_scatter = 8;
	num_in_scatter = 16;
	inner_radius = 1.0;
	surface_radius = 1.0;
	surface_margin = 0.001;
	outer_radius = 2.0;
	ph_ray = 0.05;
	ph_mie = 0.02;
	k_ray = Vector3(3.8, 13.5, 33.1);
	k_mie = Vector3(21, 21, 21);
	k_mie_ex = 1.1;
	g_mie = -0.78;
	intensity = 4.0;
	direct_irradiance_attenuation = 1.0;
	indirect_irradiance_intensity = 1.0;
	enable_shadows = true;
	shadow_bias = 0.0;

	atmosphere = VisualServer::get_singleton()->atmosphere_create();
	VS::get_singleton()->instance_set_base(get_instance(), atmosphere);
}

Atmosphere::~Atmosphere() {

	VS::get_singleton()->free(atmosphere);
}
