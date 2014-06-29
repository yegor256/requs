<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="step/signature">
        <xsl:copy>
            <xsl:variable name="text" select="."/>
            <xsl:variable name="method" select="//method[signature=$text]"/>
            <xsl:if test="$method">
                <xsl:attribute name="ref">
                    <xsl:value-of select="$method/id"/>
                </xsl:attribute>
            </xsl:if>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
