/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:24:08 by hdony             #+#    #+#             */
/*   Updated: 2023/06/30 16:11:51 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION
# define LOCATION

# include "../Webserv.hpp"
# include "Utils.hpp"

class Location
{
    private:
        /*
        ** ------------------------------- ATTRIBUTES --------------------------------
        */
        std::string                 _location_type;
        std::string                 _root;
        bool                        _autoindex;
        std::vector<std::string>    _allow_methods;
        std::string                 _index;
        std::string                 _return;
        std::string                 _alias;

    public:
        /*
    	** ------------------------------- COPLIEN --------------------------------
	    */
        Location();
        Location(std::string LocationBlock, std::string LocationType);
        Location(const Location &rhs);
        Location    &operator=(const Location &rhs);
        ~Location();

        /*
	    ** ------------------------------- ACCESSORS --------------------------------
	    */
        void                        setLocType(std::string &LocationType);
        void                        setAllowMethods(std::string &value);
        std::string                 &getLocationType();
        std::string                 &getRoot();
        bool                        &getAutoindex();
        std::vector<std::string>    &getAllowMethods();
        std::string                 &getIndex();
        std::string                 &getReturn();
        std::string                 &getAlias();
};

# endif