<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/spec/errors">
        <xsl:copy>
            <xsl:apply-templates select="error"/>
            <xsl:for-each select="//method[@seal != '']">
                <xsl:variable name="method" select="."/>
                <xsl:for-each select="attributes/attribute[@seal != '']">
                    <xsl:if test="$method/@seal != @seal">
                        <error type="seal" pos="0">
                            <xsl:attribute name="line">
                                <xsl:value-of select="$method/mentioned/where[position()=1]"/>
                            </xsl:attribute>
                            <xsl:text>Seal &quot;</xsl:text>
                            <xsl:value-of select="$method/@seal"/>
                            <xsl:text>&quot; at the method </xsl:text>
                            <xsl:value-of select="$method/id"/>
                            <xsl:text> doesn't match &quot;</xsl:text>
                            <xsl:value-of select="@seal"/>
                            <xsl:text>&quot; at the attribute &quot;</xsl:text>
                            <xsl:value-of select="text()"/>
                            <xsl:text>&quot;</xsl:text>
                        </error>
                    </xsl:if>
                </xsl:for-each>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
