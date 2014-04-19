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
                <title>NFRs</title>
                <meta name="description" content="NFRs"/>
                <meta name="keywords" content="software requirements specification"/>
                <meta name="author" content="requs"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <link rel="stylesheet" type="text/css" href="requs.css"/>
            </head>
            <body>
                <xsl:apply-templates select="/nfrs"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="nfrs">
        <h1><xsl:text>NFRs</xsl:text></h1>
        <table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Method</th>
                    <th>NFR</th>
                    <th>Description</th>
                </tr>
            </thead>
            <tbody>
                <xsl:apply-templates select="nfr"/>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="nfr">
        <tr>
            <td><xsl:value-of select="@id"/></td>
            <td><xsl:value-of select="method"/></td>
            <td><xsl:value-of select="name"/></td>
            <td><xsl:value-of select="description"/></td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
