/**
 *

 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id: index.php 2236 2010-07-03 17:26:54Z yegor256@yahoo.com $
 */

function render()
{
    // we already rendered it
    if ((render.rendered != undefined) && render.rendered == this.value) {
        return;
    }
    // save it for the future, to avoid double renderings
    render.rendered = this.value;
    
    $.ajax(
        {
            'url': "http://tracfacade.fazend.com/rqdql",
            'data': { 'text': this.value },
            'dataType': 'jsonp',
            'success': function(data)
            {
                var xml = (new DOMParser()).parseFromString(data, "text/xml");
                
                $("#result").removeClass().addClass(
                    xml.getElementsByTagName("errorsCount")[0].value > 0 ?
                    'error' : 'success'
                );
                
                $("#xml").html(data.replace(/</g, '&lt;'));
            }
        }
    );
}

/**
 * Run this method when the document is loaded
 */
$(document).ready(
    function()
    {
        $("#example").keyup(render);
    }
);
