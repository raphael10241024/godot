/*************************************************************************/
/*  decal.cpp                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
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

#include "decal.h"

#include "core/core_string_names.h"
#include "scene/scene_string_names.h"
#include "servers/visual_server.h"

void Decal::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &Decal::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &Decal::get_texture);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture");
}

void Decal::set_texture(const Ref<Texture> &p_texture) {

	if (p_texture == texture)
		return;
	texture = p_texture;
	RID rid = p_texture.is_valid() ? p_texture->get_rid() : RID();
	VS::get_singleton()->decal_set_texture(decal, rid);
}

Ref<Texture> Decal::get_texture() const {

	return texture;
}

AABB Decal::get_aabb() const {
	return AABB(Vector3(-1, -1, -1) * range, Vector3(2, 2, 2) * range);
}

PoolVector<Face3> Decal::get_faces(uint32_t p_usage_flags) const {

	return PoolVector<Face3>();
}

Decal::Decal() {

	decal = VisualServer::get_singleton()->decal_create();
	VS::get_singleton()->instance_set_base(get_instance(), decal);
}

Decal::~Decal() {

	VS::get_singleton()->instance_set_base(get_instance(), RID());
	if (decal.is_valid())
		VisualServer::get_singleton()->free(decal);
}