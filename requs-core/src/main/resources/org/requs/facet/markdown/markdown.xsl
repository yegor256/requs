<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="1.0">
    <xsl:include href="_layout.xsl"/>
    <xsl:template name="head">
        <title>markdown</title>
        <script>//<![CDATA[
            $(document).ready(
                function () {
                    $('.md').each(
                        function () {
                            $(this).html(
                                markdown.toHTML(
                                    $('<div/>').html($(this).html()).text()
                                )
                            );
                        }
                    );
                }
            );
        //]]></script>
        <script src="http://img.requs.org/markdown.min.js">
            <!-- nothing -->
        </script>
    </xsl:template>
    <xsl:template name="body">
        <xsl:apply-templates select="pages/methods/method"/>
    </xsl:template>
    <xsl:template match="method">
        <h1><xsl:value-of select="@id"/></h1>
        <div class="md"><xsl:value-of select="."/></div>
    </xsl:template>
</xsl:stylesheet>
