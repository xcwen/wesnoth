/*
	Copyright (C) 2013 by Pierre Talbot <ptalbot@mopong.net>
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/
#include "umcd/wml_reply.hpp"
#include "config.hpp"
#include <boost/lexical_cast.hpp>

namespace umcd{

wml_reply::wml_reply(){}

wml_reply::wml_reply(const config& metadata)
: metadata_(metadata.to_string())
, payload_size_(htonl(this->metadata_.size()))
{
}

std::vector<boost::asio::const_buffer> wml_reply::to_buffers() const
{
	std::vector<boost::asio::const_buffer> buffers;
	buffers.push_back(boost::asio::buffer(reinterpret_cast<const char*>(&payload_size_), sizeof(payload_size_)));
	buffers.push_back(boost::asio::buffer(metadata_));
	return buffers;
}

} // namespace umcd
