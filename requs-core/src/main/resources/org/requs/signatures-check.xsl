<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="/spec/errors">
        <xsl:copy>
            <xsl:apply-templates select="error"/>
            <xsl:for-each select="//steps/step[signature and not(starts-with(signature,'&quot;') and ends-with(signature,'&quot;'))]">
                <xsl:variable name="step" select="."/>
                <xsl:if test="/spec[not(methods/method/signature=$step/signature)]">
                    <error type="seal" pos="0">
                        <xsl:attribute name="line">
                            <xsl:value-of select="$step/mentioned/where[position()=1]"/>
                        </xsl:attribute>
                        <xsl:text>Step &quot;</xsl:text>
                        <xsl:value-of select="$step/number"/>
                        <xsl:text>&quot; refers to a non-existing use case &quot;</xsl:text>
                        <xsl:value-of select="$step/signature"/>
                        <xsl:text>&quot;</xsl:text>
                    </error>
                </xsl:if>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
