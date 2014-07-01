<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:re="http://www.requs.org"
    xmlns:r="org.requs.facet.uml.Plant" version="2.0"
    exclude-result-prefixes="xs r re">
    <xsl:import href="uml/functions.xsl"/>
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*"/>
    <xsl:template match="method">
        <xsl:copy>
            <xsl:apply-templates select="(node() except diagrams)|@*"/>
            <xsl:variable name="uml">
                <xsl:text>hide footbox&#10;</xsl:text>
                <xsl:text>title </xsl:text>
                <xsl:value-of select="id"/>
                <xsl:text>: Sequence Diagram&#10;</xsl:text>
                <xsl:apply-templates select="." mode="uml"/>
            </xsl:variable>
            <diagrams>
                <xsl:apply-templates select="diagrams/*"/>
                <diagram>
                    <uml>
                        <xsl:value-of select="$uml"/>
                    </uml>
                    <svg>
                        <xsl:value-of select="r:svg(re:plant($uml))"/>
                    </svg>
                </diagram>
            </diagrams>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="method" mode="uml">
        <xsl:for-each select="bindings/binding[not(starts-with(name, '_'))]">
            <xsl:text>participant &quot;</xsl:text>
            <xsl:value-of select="name"/>
            <xsl:text>&quot; as </xsl:text>
            <xsl:value-of select="name"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
        <xsl:for-each select="steps/step">
            <xsl:value-of select="object"/>
            <xsl:text> -&gt; </xsl:text>
            <xsl:choose>
                <xsl:when test="result">
                    <xsl:value-of select="result"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="object"/>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:text> : </xsl:text>
            <xsl:value-of select="re:signature(signature)"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
