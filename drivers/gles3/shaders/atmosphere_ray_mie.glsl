[vertex]

layout(location=0) in highp vec4 vertex_attrib;
layout(location=4) in vec2 uv_in;
out vec2 uv_interp;

void main() {
	uv_interp = uv_in;
	gl_Position = vertex_attrib;
}


[fragment]

#define M_PI 3.14159265359
#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38
#define DBL_MAX 1.7976931348623158e+308
#define DBL_MIN 2.2250738585072014e-308

layout(location=0) out vec4 frag_color;
in vec2 uv_interp;

uniform float atmosphere_outer_radius;
uniform float atmosphere_inner_radius;
uniform float atmosphere_ph_ray;
uniform float atmosphere_ph_mie;
uniform int atmosphere_num_out_scatter;


// ray intersects circle
// e = -b +/- sqrt( b^2 - c )
vec2 intersectRayCircle(vec2 ray_origin, vec2 ray_dir, float radius_squared) {
	float b = dot(ray_origin, ray_dir);
	float c = dot(ray_origin, ray_origin) - radius_squared;
	if (c > 0.0 && b > 0.0)	// ray outside of sphere and pointing away
		return vec2(FLT_MAX, -FLT_MAX);
	float d = b * b - c;
	if (d < 0.0)	// ray missing sphere
		return vec2(FLT_MAX, -FLT_MAX);
	d = sqrt( d );
	return vec2(max(0.0,-b-d), -b+d);
}


// Density at a given height above atmosphere's inner radius
float atmosphereDensity(float height, float ph) {
	return exp( -height / ph );
}


// Optical depth from any ray starting inside the atmosphere
void atmosphereOpticalLength( in vec2 ray_orig, in vec2 ray_dir, out float ray, out float mie ) {
	vec2 f = intersectRayCircle(ray_orig, ray_dir, atmosphere_outer_radius * atmosphere_outer_radius);
	float out_step_len = f.y / float(atmosphere_num_out_scatter);
	vec2 out_step = ray_dir * out_step_len;
	vec2 out_pos = ray_orig + out_step * 0.5;
	ray = 0.0;
	mie = 0.0;
	for (int o = 0; o < atmosphere_num_out_scatter; o++) {
		float height = max(length(out_pos) - atmosphere_inner_radius, 0.0);
		ray += atmosphereDensity(height, atmosphere_ph_ray);
		mie += atmosphereDensity(height, atmosphere_ph_mie);
		out_pos += out_step;
	}
	ray *= out_step_len;
	mie *= out_step_len;
}


void main() {
	float distance2center = atmosphere_inner_radius + uv_interp.x * (atmosphere_outer_radius - atmosphere_inner_radius);
	float angle2zenith = uv_interp.y * 2.0 - 1.0;

	float height = max(distance2center - atmosphere_inner_radius, 0.0);
	float d_ray = atmosphereDensity(height, atmosphere_ph_ray);
	float d_mie = atmosphereDensity(height, atmosphere_ph_mie);

	vec2 ray_dir = normalize(vec2(sqrt(1.0-angle2zenith*angle2zenith), angle2zenith));
	vec2 ray_orig = vec2(0.0, distance2center);
	float n_ray = 0.0;
	float n_mie = 0.0;
	atmosphereOpticalLength(ray_orig, ray_dir, n_ray, n_mie);

	frag_color = vec4(d_ray,n_ray,d_mie,n_mie);
}
