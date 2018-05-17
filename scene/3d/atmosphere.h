/*************************************************************************/
/*  atmosphere.h                                                         */
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

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include "scene/3d/visual_instance.h"
#include "scene/resources/sky_box.h"

class Atmosphere : public VisualInstance {
	GDCLASS(Atmosphere, VisualInstance);

private:
	RID atmosphere;
	unsigned int num_out_scatter;
	unsigned int num_in_scatter;
	float inner_radius;
	float surface_radius;
	float surface_margin;
	float outer_radius;
	float ph_ray;
	float ph_mie;
	Vector3 k_ray;
	Vector3 k_mie;
	float k_mie_ex;
	float g_mie;
	float intensity;
	float direct_irradiance_attenuation;
	float indirect_irradiance_intensity;
	bool enable_shadows;
	float shadow_bias;

protected:
	static void _bind_methods();

public:
	void set_num_out_scatter(unsigned int p_num_out_scatter);
	unsigned int get_num_out_scatter() const;

	void set_num_in_scatter(unsigned int p_num_in_scatter);
	unsigned int get_num_in_scatter() const;

	void set_inner_radius(float p_inner_radius);
	float get_inner_radius() const;

	void set_surface_radius(float p_surface_radius);
	float get_surface_radius() const;

	void set_surface_margin(float p_surface_margin);
	float get_surface_margin() const;

	void set_outer_radius(float p_outer_radius);
	float get_outer_radius() const;

	void set_ph_ray(float p_ph_ray);
	float get_ph_ray() const;

	void set_ph_mie(float ph_mie);
	float get_ph_mie() const;

	void set_k_ray(const Vector3 & p_k_ray);
	Vector3 get_k_ray() const;

	void set_k_mie(const Vector3 & p_k_mie);
	Vector3 get_k_mie() const;

	void set_k_mie_ex(float p_k_mie_ex);
	float get_k_mie_ex() const;

	void set_g_mie(float p_g_mie);
	float get_g_mie() const;

	void set_intensity(float p_intensity);
	float get_intensity() const;

	void set_direct_irradiance_attenuation(float p_attenuation);
	float get_direct_irradiance_attenuation() const;

	void set_indirect_irradiance_intensity(float p_intensity);
	float get_indirect_irradiance_intensity() const;

	void set_enable_shadows(bool p_enable);
	bool are_shadows_enabled() const;

	void set_shadow_bias(float p_bias);
	float get_shadow_bias() const;

	virtual AABB get_aabb() const;
	virtual PoolVector<Face3> get_faces(uint32_t p_usage_flags) const;

	Atmosphere();
	~Atmosphere();
};

#endif // ATMOSPHERE_H
