<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns="http://www.w3.org/1999/xhtml" version="2.0"
    exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/">
        <html lang="en">
            <head>
                <title>markdown</title>
                <meta name="description" content="markdown"/>
                <meta name="keywords" content="software requirements specification"/>
                <meta name="author" content="requs"/>
                <meta name="viewport" content="width=device-width" />
                <link rel="stylesheet" type="text/css" href="requs.css"/>
                <script src="https://code.jquery.com/jquery-2.1.1-rc1.js">
                    <!-- nothing -->
                </script>
                <script>//<![CDATA[
                    $(document).ready(
                        function () {
                            $('.md').each(
                                function () {
                                    $(this).html(markdown.toHTML($(this).html()));
                                }
                            );
                        }
                    );
                //]]></script>
                <script src="http://img.requs.org/markdown.min.js">
                    <!-- nothing -->
                </script>
            </head>
            <body>
                <xsl:apply-templates select="pages/methods/method"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="method">
        <h1><xsl:value-of select="@id"/></h1>
        <div class="md"><xsl:value-of select="."/></div>
    </xsl:template>
</xsl:stylesheet>
